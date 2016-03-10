//source file for nnet.h
//all definitions in header file
#include "nnet.h"
#include "movement.h"
//#include "alphbeta.h"
#include <cmath>
using std::exp;
#include <string>
using std::string;
using std::getline;
#include <stdexcept>
using std::runtime_error;
#include <fstream>
using std::ifstream;
using std::ofstream;
#include <functional>
using std::function;
#include <utility>
using std::pair;
using std::make_pair;
#include <algorithm>
#include <vector>
using std::vector;
#include <map>
using std::map;

//debug -- remove later --
#include <iostream>
using std::cout;
using std::endl;
//end debug

struct mov{
    public:
    mov(string b, mov * p, bool m=true):current(b),pops(p),max(m)
    {}
    void make_babies(bool red){
        auto temp = getBoardsN({current}, red);
        for(int i = 0; i < temp.size(); ++i){
            kodomo.push_back(mov(temp[i], this, !max));
        }
    }
    vector<mov> get_kids() { return kodomo; }
    void set_score(double a) { score = a; }
    bool isMax() { return max; }
    string get_cur() { return current; }
    double get_score() { return score; }
    mov * get_pops() { return pops; }
    private:
    string current;
    vector<mov> kodomo;
    double score;
    bool max;
    mov * pops;
};


vector<double> deString(string board, bool red, double king = 1.5){
    vector<double> rvec;
    if(red){
        for(int i = 0; i < 32; ++i){
            switch(board[i]){
                case 'r' : rvec.push_back(1); break;
                case 'b' : rvec.push_back(-1); break;
                case 'R' : rvec.push_back(king); break;
                case 'B' : rvec.push_back(king * -1); break;
                case '_' : rvec.push_back(0); break;
                default : cout << "DEFAULT!!!!" << endl;
            }
        }
    }else{
        for(int i = 0; i < 32; ++i){
            switch(board[i]){
                case 'r' : rvec.push_back(-1); break;
                case 'b' : rvec.push_back(1); break;
                case 'R' : rvec.push_back(king*-1); break;
                case 'B' : rvec.push_back(king); break;
                case '_' : rvec.push_back(0); break;
                default : cout << "DEFAULT!!!!" << endl;
            }
        }
    }
    return rvec;
}



inline static double sigmoid(double sum, const double a, double b, const double c){
    if(b==0)
        b=1;
    if(sum < 0)
        return (a/(1.0+exp(sum/b)))+c;
    else
        return (a/(1.0+exp((sum*-1))))+c;
}

neuralNet::neuralNet(const string & path){
    vector<size_t> levels;
    vector<double> weights;
    size_t incount;
    ifstream loadnet(path.c_str());
    if(!loadnet)
        throw runtime_error("file not found");

    loadnet >> incount;
    for(size_t i = 0; i < incount; ++i){
        size_t temp;
        loadnet >> temp;
        levels.push_back(temp);
    }
    levels_ = levels;
    loadnet >> incount;
    for(size_t i = 0; i < incount; ++i){
        double temp;
        loadnet >> temp;
        weights.push_back(temp);
    }

    if(levels_.size()<=0)
        throw runtime_error("Need more levels!");

    if(levels_.back()!=1)
        throw runtime_error("Too many nodes in last level! Expected 1, got "+ std::to_string(levels_.back()) + "!");

   makeNodeLevels();
   setWeights(weights);
}

neuralNet::neuralNet(const vector<size_t> & levels, const vector<double> & weights):levels_(levels)
{
    if(levels_.size()<=0)
        throw runtime_error("Need more levels!");

    if(levels_.back()!=1)
        throw runtime_error("Too many nodes in last level! Expected 1, got "+ std::to_string(levels_.back()) + "!");

   makeNodeLevels();
   setWeights(weights);
}


double neuralNet::evaluate(const vector<double> & input, const double a, const double b, const double c){
    for(size_t i = 0; i < nodeLevels_[0].size(); ++i)
        nodeLevels_[0][i].value = input[i];

    for(size_t i = 1; i < nodeLevels_.size(); ++i){
        for(size_t j = 0; j < nodeLevels_[i].size(); ++j){
            double temp = 0;
                for(size_t k = 0; k <nodeLevels_[i-1].size(); ++k)
                    temp += nodeLevels_[i-1][k].value * nodeLevels_[i-1][k].weights[j];

            nodeLevels_[i][j].value = sigmoid(temp, a, b, c);
                }
       }

       return nodeLevels_[nodeLevels_.size()-1][0].value;
}

double minimax(string board, bool red, neuralNet & net, int depth = 9){
    auto check = getBoardsN({board},red);
    if(check.size() <= 0){
        return 9001;
    }
    mov head(board, nullptr);
    head.make_babies(red);
    vector<mov*> tree;
    for(int i = 0; i < depth; ++i){
        for(auto j : head.get_kids()){
            j.make_babies(red);
            tree.push_back(&j);
        }
    }
    for(int i = tree.size()-1; i > 0; --i){
        tree[i]->set_score(net.evaluate(deString(tree[i]->get_cur(),red)));
    }
   // for(int i = tree.size()-1; i > 0; --i){
       // if(tree[i]->isMax()){
          //  auto temp = tree[i]->get_pops();
            //if(temp->get_score() <= tree[i]->get_score())
                //temp->set_score(tree[i]->get_score());
      //  }else{
      //      auto temp = tree[i]->get_pops();
            //if(temp->get_score() >= tree[i]->get_score())
                //temp->set_score(tree[i]->get_score());
      //  }
   // }
    
    map<string, double> moveses;
    for(int i = 0; i < check.size(); ++i){
        moveses[tree[i]->get_cur()] = tree[i]->get_score();
    }
    return moveses[board];
}


void neuralNet::evolve(const string & path, function<double(double)> evolver){
   ofstream writeNet(path.c_str());
   if(!writeNet)
      throw runtime_error("invalid filename");
   
   writeNet << levels_.size() << '\n';
   for(size_t i = 0; i < levels_.size(); ++i)
      writeNet << levels_[i] << " ";
   writeNet << '\n';

    vector<double*> realWeights;

    for(auto & level:nodeLevels_)
        for(auto & node:level)
            for(auto & weight:node.weights)
                realWeights.push_back(&weight);

   writeNet << realWeights.size() << '\n';
   for(size_t i = 0; i < realWeights.size(); ++i)
      writeNet << evolver(*realWeights[i]) << " ";

  writeNet.close(); 
}

pair<string,bool> neuralNet::go(const string & board, bool red){

    //      CALLS TO ALPHA BETA GO HERE      \\
    
    /*node * passer;
    passer = new node(board);
    return absearch(passer,5, red, *this);*/
    
    vector<pair<double, string> > weighedBoards;
    vector<string> pboard = {board};
    vector<string> boards;
    if(red)
        boards = getBoardsN(pboard, 1);
    else
        boards = getBoardsN(pboard, 0);
        
    for(int i = 1; i < boards.size(); ++i)
        weighedBoards.push_back(make_pair(minimax(boards[i],red, *this),boards[i]));

    //for(int i = 1; i < boards.size(); ++i)
       // weighedBoards.push_back(make_pair(evaluate(deString(boards[i])),boards[i]));
        
    if(weighedBoards.size() > 0 /*&& red*/){
        std::sort(weighedBoards.begin(), weighedBoards.end());
        return make_pair(weighedBoards[0].second, true);
    }/*else if(weighedBoards.size() > 0 && !red){
        std::sort(weighedBoards.begin(), weighedBoards.end());
        return make_pair(weighedBoards[weighedBoards.size()-1].second, true);
    }*/else{
        return make_pair("end", false);
    }
    
}

void neuralNet::makeNodeLevels(){
    nodeLevels_.clear();

    for(size_t i = 0; i < levels_.size(); ++i){
        if(i + 1 < levels_.size()){
            vector<node_> nodeLevel;

            for(size_t j = 0; j < levels_[i]; ++j){
                node_ node;
                node.value = 0;
                node.weights.resize(levels_[i+1], 1);
                nodeLevel.push_back(node);
            }

            nodeLevels_.push_back(nodeLevel);
        }
        else{
            node_ node;
            node.value = 5;
            node.weights.clear();
            nodeLevels_.push_back({node});
        }
    }
}

void neuralNet::setWeights(const vector<double> & weights){
    vector<double*> realWeights;
    for(auto & level:nodeLevels_)
        for(auto & node:level)
            for(auto & weight:node.weights)
                realWeights.push_back(&weight);

    if(weights.size() < realWeights.size())
        throw runtime_error("Not enough weights! Got " + std::to_string(weights.size()) + ", but I need " + std::to_string(realWeights.size()));
    else if(weights.size() > realWeights.size())
        throw runtime_error("Too many weights! Got " + std::to_string(weights.size()) + ", but I need " + std::to_string(realWeights.size()));

    for(size_t i = 0; i < realWeights.size(); ++i)
        *(realWeights[i]) = weights[i];
}
