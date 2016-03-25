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

double alphabeta(move & board, int depth, double alpha, double beta, bool max, bool red){
    if(depth == 0 || board.get_kids().size() <= 1)
        return board.get_net()->evaluate(board.get_current(),red);
    
    if(max){
        double r_score = -10000;
        for(auto & i : board.get_kids()){
            auto temp = alphabeta(*i, depth-1, alpha, beta, false, !red);
            if(temp > r_score)
                r_score = temp;
            if(r_score > alpha)
                alpha = r_score;
            if(beta <= alpha)
                break;
        }
        return r_score;
    }else{
        double r_score = 10000;
        for(auto & i : board.get_kids()){
            auto temp = alphabeta(*i, depth-1, alpha, beta, true, !red);
            if(temp < r_score)
                r_score = temp;
            if(r_score > alpha)
                alpha = r_score;
            if(beta <= alpha)
                break;
        }
        return r_score;
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
    for(auto & i : head.get_kids())
        for(auto & j : i->get_kids())
            for(auto & k : j->get_kids())
                for(auto & l : k->get_kids())
                    for(auto & m : l->get_kids())
                        for(auto & n : m->get_kids())
                            n->make_kids(red);
                            
    for(auto & i : head.get_kids()){
        for(auto & j : i->get_kids()){
            for(auto & k : j->get_kids()){
                for(auto & l : k->get_kids()){
                    for(auto & m : l->get_kids()){
                        for(auto & n : m->get_kids()){
                            pick(*n, true, red);
                        }
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

string minimaxAB(string board_start, neuralNet & net, bool red){
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
    for(auto & i : head.get_kids())
        for(auto & j : i->get_kids())
            for(auto & k : j->get_kids())
                for(auto & l : k->get_kids())
                    for(auto & m : l->get_kids())
                        for(auto & n : m->get_kids())
                            n->make_kids(red);
                 
    //  for(auto & i : head.get_kids())
    //     for(auto & j : i->get_kids())
    //         for(auto & k : j->get_kids())
    //             for(auto & l : k->get_kids())
    //                 for(auto & m : l->get_kids())
    //                     for(auto & n : m->get_kids())
    //                         pick(*n, true, red);
                                       
    
    vector<pair<double, string> > rboards;
    
    
    for(auto & i : head.get_kids())
        rboards.push_back(make_pair(alphabeta(*i, 6, -10000, 10000, true, red), i->get_current()));
    if(rboards.size() <= 0){
        return "end";
    }else{
        sort(rboards.begin(), rboards.end());
        return rboards[rboards.size()-1].second;
    }
}