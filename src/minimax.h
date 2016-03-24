#ifndef MINIMAX_H_INCLUDED
#define MINIMAX_H_INCLUDED

#include "nnet.h"
#include "movement.h"

#include <vector>
using std::vector;
#include <memory>
using std::shared_ptr;
using std::make_shared;


struct move{
public:
    move(string board, neuralNet & net):current_(board),net_(make_shared<neuralNet>(net)), set_(false)
    {}
    move(string board, shared_ptr<neuralNet> net):current_(board),net_(net),set_(false)
    {} 
            

    void make_kids(bool red){
        auto temp = getBoardsN({current_}, red);
        if(temp.size() > 1) 
            for(int i = 1; i < temp.size(); ++i)
                kids_.push_back(make_shared<move>(move(temp[i],net_)));
        else
            return;
    }

    void set_score(double a){
        set_ = true;
        score_ = a;
    }vector<shared_ptr<move> > get_kids(){
        return kids_;
    }double get_score(){
        return score_;
    }string get_current(){
        return current_;
    }shared_ptr<neuralNet> get_net(){
        return net_;
    }
    bool not_set(){
        return !set_;
    }

private:
    vector<shared_ptr<move> > kids_;
    string current_;
    double score_;
    shared_ptr<neuralNet> net_;
    bool set_;
};

void pick(move & board, bool max, bool red);

string minimax(string board_start, neuralNet & net, bool red);

#endif
