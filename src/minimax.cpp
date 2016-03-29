#include "minimax.h"
#include <algorithm>
using std::sort;

//DEBUG
#include <iostream>
using std::cout;
using std::endl;
#include <chrono>
using std::chrono::steady_clock;

int ab_count = 0;
int mm_count = 0;
int dfs_count = 0;
//END DEBUG

double pick(move & board, int depth, bool max, bool red){
    mm_count++;
    if(depth == 0 || board.get_kids().size() <= 0)
       return board.get_score();

    if(max){
        double r_score = -10000;
        for(auto & i : board.get_kids()){
            auto temp = pick(*i, depth-1, false, !red);
            if(temp > r_score)
                r_score = temp;
        }
        return r_score;
    }else{
        double r_score = 10000;
        for(auto & i : board.get_kids()){
            auto temp = pick(*i, depth-1, true, !red);
            if(temp < r_score)
                r_score = temp;
        }
        return r_score;
    }
}

double alphabeta(move & board, int depth, double alpha, double beta, bool max, bool red){
    ab_count++;
    if(depth == 0 || board.get_kids().size() <= 0)
        return board.get_score();
    
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
            if(r_score < beta)
                beta = r_score;
            if(beta <= alpha)
                break;
        }
        return r_score;
    }
}

string minimax(string board_start, neuralNet & net, bool red){
    auto b = steady_clock::now();
    
    
    move head(board_start, net);
    head.make_kids(red);
    
    if(head.get_kids().size() == 1)
        return head.get_kids()[0]->get_current();
    if(head.get_kids().size() <= 0)
        return "end";

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
                            
    vector<pair<double, string> > rboards;

    for(auto & i : head.get_kids())
        rboards.push_back(make_pair(pick(*i,6,true,red), i->get_current()));

    
    sort(rboards.begin(), rboards.end());
    auto e = steady_clock::now();
    auto diff = e - b;

    cout << "MM: " << rboards[rboards.size()-1].second << " " << mm_count << " " << std::chrono::duration<double>(diff).count() << endl;
    mm_count = 0;
    return rboards[rboards.size()-1].second;
}

string minimaxAB(string board_start, neuralNet & net, bool red){
    auto b = steady_clock::now();
    move head(board_start, net);
    head.make_kids(red);
    
    if(head.get_kids().size() == 1)
        return head.get_kids()[0]->get_current();
    if(head.get_kids().size() <= 0)
        return "end";

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
                 
    vector<pair<double, string> > rboards;
    
    for(auto & i : head.get_kids())
        rboards.push_back(make_pair(alphabeta(*i, 6, -10000, 10000, true, red), i->get_current()));
    

    
    sort(rboards.begin(), rboards.end());
    auto e = steady_clock::now();
    auto diff = e - b;

    cout << "AB: " << rboards[rboards.size()-1].second << " " << ab_count << " " << std::chrono::duration<double>(diff).count() << endl;
    ab_count = 0;
    return rboards[rboards.size()-1].second;
}


//DFS attempt
double alphabeta_dfs(move & board, int depth, double alpha, double beta, bool max, bool red){
    dfs_count++;

    board.make_kids(red);

    if(depth == 0 || board.get_kids().size() <= 0)
        return board.get_score();
    
    if(max){
        double r_score = -10000;
        for(auto & i : board.get_kids()){
            auto temp = alphabeta_dfs(*i, depth-1, alpha, beta, false, !red);
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
            auto temp = alphabeta_dfs(*i, depth-1, alpha, beta, true, !red);
            if(temp < r_score)
                r_score = temp;
            if(r_score < beta)
                beta = r_score;
            if(beta <= alpha)
                break;
        }
        return r_score;
    }
}

string minimax_dfs(string board_start, neuralNet & net, bool red){
    auto b = steady_clock::now();
    move head(board_start, net);
    head.make_kids(red);
    
    if(head.get_kids().size() == 1)
        return head.get_kids()[0]->get_current();
    if(head.get_kids().size() <= 0)
        return "end";
        
    vector<pair<double, string> > rboards;
    
    for(auto & i : head.get_kids())
        rboards.push_back(make_pair(alphabeta_dfs(*i, 6, -10000, 10000, true, !red), i->get_current()));
    

    
    sort(rboards.begin(), rboards.end());
    auto e = steady_clock::now();
    auto diff = e - b;

    cout << "DF: " << rboards[rboards.size()-1].second << " " << dfs_count << " " << std::chrono::duration<double>(diff).count() << endl;
    dfs_count = 0;
    return rboards[rboards.size()-1].second;
}
