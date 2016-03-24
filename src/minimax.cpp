#include "minimax.h"
#include <algorithm>
using std::sort;
#include <iostream>
using std::cout;
using std::endl;

void pick(move & board, bool max, bool red){
    if(board.get_kids().size() <= 1)
        return;
    for(int i = 0; i < board.get_kids().size(); ++i)
        if(board.get_kids()[i]->not_set())
            board.get_kids()[i]->set_score(board.get_net()->evaluate(board.get_kids()[i]->get_current(), red));

    if(max){
        board.set_score(-1000);
        for(int i = 0; i < board.get_kids().size(); ++i)
            if(board.get_kids()[i]->get_score() > board.get_score())
               board.set_score(board.get_kids()[i]->get_score());
        
    }else{
        board.set_score(1000);
        for(int i = 0; i < board.get_kids().size(); ++i)
            if(board.get_kids()[i]->get_score() < board.get_score())
               board.set_score(board.get_kids()[i]->get_score());
    }
}

string minimax(string board_start, neuralNet & net, bool red){
    move head(board_start, net);
    head.make_kids(red);

    for(auto & i : head.get_kids())
        i->make_kids(!red);
    for(auto & i : head.get_kids())
        for(auto & j : i->get_kids())
            j->make_kids(red);
    for(auto & i : head.get_kids())
        for(auto & j : i->get_kids())
            for(auto & k : j->get_kids())
                k->make_kids(!red);
    for(auto & i : head.get_kids())
        for(auto & j : i->get_kids())
            for(auto & k : j->get_kids())
                for(auto & l : k->get_kids())
                    l->make_kids(red);
    for(auto & i : head.get_kids())
        for(auto & j : i->get_kids())
            for(auto & k : j->get_kids())
                for(auto & l : k->get_kids())
                    for(auto & m : l->get_kids())
                        m->make_kids(!red);
    for(auto & i : head.get_kids()){
        for(auto & j : i->get_kids()){
            for(auto & k : j->get_kids()){
                for(auto & l : k->get_kids()){
                    for(auto & m : l->get_kids()){
                        pick(*m, false, red); 
                    }
                    pick(*l, true, red);
                }
                pick(*k, false, red);
            }
            pick(*j, true, red);
        }
        pick(*i, false, red);
    }
    pick(head, true, red);
    vector<pair<double, string> > rboards;

    for(auto & i : head.get_kids())
        rboards.push_back(make_pair(i->get_score(), i->get_current()));
    if(rboards.size() <= 0){
        return "end";
    }else{
        sort(rboards.begin(), rboards.end());
        return rboards[rboards.size()-1].second;
    }
}
