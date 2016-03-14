#ifndef MINIMAX_H_INCLUDED
#define MINIMAX_H_INCLUDED

#include "nnet.h"
#include "movement.h"

#include <vector>
using std::vector;
#include <string>
using std::string;
#include <memory>
using std::shared_ptr;
using std::make_shared;


struct move{
public:
    move(string board, neuralNet & net):current_(board),net_(make_shared<neuralNet>(net)), parent_(nullptr)
    {}
    move(string board, shared_ptr<move> pops, shared_ptr<neuralNet> net):current_(board),net_(net),parent_(pops)
    {} 

    void make_kids(bool red){
            auto temp = getBoardsN(current_, red);
        for(int i = 0; i < temp.size(); ++i)
            kids_.push_back(make_shared<move>(move(temp[i],make_shared<move>(*this),net_)));
    }

    void set_score(double a){
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

private:
    vector<shared_ptr<move> > kids_;
    shared_ptr<move> parent_;
    string current_;
    double score_;
    shared_ptr<neuralNet> net_;
};

void pick(move & board, bool max);

string minimax(string board_start, neuralNet & net, bool red, int depth = 9);

#endif
