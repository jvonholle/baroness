//source file for nnet.h
//all definitions in header file
//#include "nnet.h"
//#include "movement.h"
//#include "alphbeta.h"
#include "minimax.h"
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

//debug -- remove later --
#include <iostream>
using std::cout;
using std::endl;
//end debug


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
                default : cout << "DEFAULT BECAUSE: " << board[i] << endl;
            }
        }
        return rvec;
    }else{
        for(int i = 0; i < 32; ++i){
            switch(board[i]){
                case 'r' : rvec.push_back(-1); break;
                case 'b' : rvec.push_back(1); break;
                case 'R' : rvec.push_back(king*-1); break;
                case 'B' : rvec.push_back(king); break;
                case '_' : rvec.push_back(0); break;
                default : cout << "DEFAULT BECAUSE: " << board[i] << endl;
            }
        }
        return rvec;
    }
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

double neuralNet::evaluate(const string & inputS, const double a, const double b, const double c, const bool red){
    vector<double> input = deString(inputS, red);
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
    
    string rstring = minimax(board, *this, red); 
    bool rbool = (rstring != "end");

    return make_pair(rstring, rbool);

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
