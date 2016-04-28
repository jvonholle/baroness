#include "minimax.h"
#include <algorithm>
using std::sort;
#include <tuple>
using std::tuple;
using std::get;
using std::make_tuple;

//DEBUG
#include <iostream>
using std::cout;
using std::endl;
#include <chrono>
using std::chrono::steady_clock;

int dfs_count = 0;
int nl_count = 0;
//END DEBUG

//alphabeta_dfs
//depth-first minimax searc with alpha-beta pruning of children of the passed node
//takes a node, int for how deep to go, alpha & beta values, bool for max, bool for player side and time cuttoff
//returns best score it can find
tuple<double, double, double> alphabeta_dfs(move_node & board, const int & depth, double alpha, double beta, const bool & max, const bool & red, const double & cuttoff){
    // dfs_count++;
    auto b = steady_clock::now();
    

    board.make_kids(red);
    

    if(depth == 0 || board.get_kids().size() <= 0 || cuttoff <= 0)
        return make_tuple(board.get_score(), alpha, beta);
    
    if(max){
        double r_score = -10000;
        for(auto & i : board.get_kids()){
            auto temp = alphabeta_dfs(*i, depth-1, alpha, beta, false, !red, (cuttoff-(std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000)));
            if(get<0>(temp) > r_score)
                r_score = get<0>(temp);
            if(r_score > alpha)
                alpha = r_score;
            if(beta <= alpha)
                break;
        }
        return make_tuple(r_score, alpha, beta);
    }else{
        double r_score = 10000;
        for(auto & i : board.get_kids()){
            auto temp = alphabeta_dfs(*i, depth-1, alpha, beta, true, !red, (cuttoff-(std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000)));
            if(get<0>(temp) < r_score)
                r_score = get<0>(temp);
            if(r_score < beta)
                beta = r_score;
            if(beta <= alpha )
                break;
        }
        return make_tuple(r_score, alpha, beta);
    }
}

//alphabeta_id
//iteraterative deepening depth-fisrt search of children of passed node, iterates based on time, goal is to go as deep as possible in under 15 seconds
//takes move_node, preferable the head node from current board, and a bool for the side the player is
//  depth - keeps track of deptht to call dfs with, increases as loop goes on
//  timec - current time elapsed from start as a double, set many times to stay accurate
//  b - begin time
//  turnt - time of last turn, used to estimate if another dfs can be called
//  timeR - variable to pass as cuttoff for dfs function, mainly helper to stay DRY
//sets children to values returned by dfs
void alphabeta_id(move_node & board, const bool & red){
    nl_count++;
    auto b = steady_clock::now();
    int depth = 1;
    double timec = (std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000.0);
    board.make_kids(red);
    double turnt =0;
    double timeR = 8.6;
   
    if(board.get_kids().size() <= 1)
        return;
    
    do{
        timec = (std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000.0);
       // timeR -= timec;
        turnt = timec;
        
        auto temp = alphabeta_dfs(*board.get_kids()[0], depth, -10000, 10000, true, red, (timeR-timec));
        board.get_kids()[0]->set_score(get<0>(temp));
        
        timec = (std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000.0);
       // timeR -= timec;
        turnt = timec - turnt;
        
        for(int i = 1; i < board.get_kids().size(); ++i){
            timec = (std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000.0);
            // timeR -= timec;
            if(timec+turnt >= 14.7)
                break;
            turnt = timec;
            temp = alphabeta_dfs(*board.get_kids()[i], depth, get<1>(temp), get<2>(temp), true, red, (timeR-timec));
            board.get_kids()[i]->set_score(get<0>(temp));
            
            timec = (std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000.0);
            // timeR -= timec;
            turnt = timec - turnt;
            if(timec >= 14.7)
                break;
        }
        depth++;
        timec = (std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000.0);
        board.sort_kids();
    }while(timec+turnt <= 14.6 && timeR>=1.4);
}

//
string minimax(const string & board_start, neuralNet & net, const bool & red){
    auto b = steady_clock::now();
    move_node head(board_start, net);
    move_node test_head(board_start, net);
        
    alphabeta_id(head,red);
    
    if(head.get_kids().size() <= 0)
        return "end";
        
    head.sort_kids();
    auto e = steady_clock::now();
    auto diff = e-b;
    
/*    cout << head.get_kids()[0]->get_current();
    if(std::chrono::duration<double>(diff).count() >= 15.0)
        cout << "!" << std::chrono::duration<double>(diff).count();
    cout << endl;
    nl_count = 0;
    dfs_count = 0;*/
    return head.get_kids()[0]->get_current();
}
