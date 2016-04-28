#ifndef MINIMAX_H_INCLUDED
#define MINIMAX_H_INCLUDED

#include "nnet.h"
#include "movement.h"

#include <vector>
using std::vector;
#include <memory>
using std::shared_ptr;
using std::make_shared;
#include <algorithm>
#include <tuple>
using std::tuple;


struct move_node{
public:
    move_node(string board, neuralNet & net):current_(board),net_(make_shared<neuralNet>(net))
    {}
    move_node(string board, shared_ptr<neuralNet> net, bool red):current_(board),net_(net)
    { score_ = net_->evaluate(current_, 1, 2, 0, red); } 
            

    void make_kids(bool red){
        if(kids_.size()>0)
            return;
        auto temp = getBoardsN({current_}, red);
        if(temp.size() > 0){
            for(int i = 0; i < temp.size(); ++i){
                kids_.push_back(make_shared<move_node>(move_node(temp[i],net_,red)));
            }
            std::sort(kids_.begin(), kids_.end(), [&](shared_ptr<move_node> a, shared_ptr<move_node> b){return (a->get_score()>b->get_score());});
        }
        else
            return;
    }
    
    void make_kids(bool red, shared_ptr<neuralNet> net){
        if(kids_.size()>0)
            kids_.clear();
        auto temp = getBoardsN({current_}, red);
        if(temp.size() > 0){
            for(int i = 0; i < temp.size(); ++i){
                kids_.push_back(make_shared<move_node>(move_node(temp[i],net,red)));
            }
            std::sort(kids_.begin(), kids_.end(), [&](shared_ptr<move_node> a, shared_ptr<move_node> b){return (a->get_score()>b->get_score());});
        }
        else
            return;
    }

    vector<shared_ptr<move_node> > get_kids(){
        return kids_;
    }double get_score(){
        return score_;
    }string get_current(){
        return current_;
    }shared_ptr<neuralNet> get_net(){
        return net_;
    }void sort_kids(){
        std::sort(kids_.begin(), kids_.end(), [&](shared_ptr<move_node> a, shared_ptr<move_node> b){return (a->get_score()>b->get_score());});
    }void set_score(double i){
        score_ = i;
    }

private:
    vector<shared_ptr<move_node> > kids_;
    const string current_;
    double score_;
    shared_ptr<neuralNet> net_;
};


string minimax(const string & board_start, neuralNet & net, const bool & red);
// string minimax_noloop(const string & board_start, neuralNet & net, const bool & red);
tuple<double, double, double> alphabeta_dfs(move_node & board, const int & depth, double alpha, double beta, const bool & max, const bool & red, const double & cuttoff);
#endif
