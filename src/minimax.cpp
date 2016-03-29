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

double alphabeta_dfs(move & board, int depth, double alpha, double beta, bool max, bool red, double time){
    auto b = steady_clock::now();
    dfs_count++;

    board.make_kids(red);

    if(depth == 0 || board.get_kids().size() <= 0 || time >= 9)
        return board.get_score();
    
    if(max){
        double r_score = -10000;
        for(auto & i : board.get_kids()){
            auto temp = alphabeta_dfs(*i, depth-1, alpha, beta, false, !red, (std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000));
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
            auto temp = alphabeta_dfs(*i, depth-1, alpha, beta, true, !red, (std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000));
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
        
    vector<pair<double, string> > rboards;
    
    for(auto & i : head.get_kids())
        rboards.push_back(make_pair(alphabeta_dfs(*i, 20, -10000, 10000, true, !red, (std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000)), i->get_current()));
    

    
    sort(rboards.begin(), rboards.end());
    auto e = steady_clock::now();
    auto diff = e - b;

//    cout << "DF: " << rboards[rboards.size()-1].second << " " << dfs_count << " " << std::chrono::duration<double>(diff).count() << endl;
    dfs_count = 0;
    return rboards[rboards.size()-1].second;
}
