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


struct move{
public:
    move(string board, neuralNet & net):current_(board),net_(make_shared<neuralNet>(net))
    {}
    move(string board, shared_ptr<neuralNet> net, bool red):current_(board),net_(net)
    { score_ = net_->evaluate(board, red); } 
            

    void make_kids(bool red){
        auto temp = getBoardsN({current_}, red);
        if(temp.size() > 1){
            for(int i = 1; i < temp.size(); ++i){
                kids_.push_back(make_shared<move>(move(temp[i],net_,red)));
            }
            std::sort(kids_.begin(), kids_.end(), [&](shared_ptr<move> a, shared_ptr<move> b){return (a->get_score()>b->get_score());});
        }
        else
            return;
    }

    vector<shared_ptr<move> > get_kids(){
        return kids_;
    }double get_score(){
        return score_;
    }string get_current(){
        return current_;
    }shared_ptr<neuralNet> get_net(){
        return net_;
    }

private:
    vector<shared_ptr<move> > kids_;
    string current_;
    double score_;
    shared_ptr<neuralNet> net_;
};


string minimax(string board_start, neuralNet & net, bool red);

#endif
