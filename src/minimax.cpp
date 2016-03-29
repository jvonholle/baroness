#include "minimax.h"
#include <algorithm>
using std::sort;

//DEBUG
#include <iostream>
using std::cout;
using std::endl;
#include <chrono>
using std::chrono::steady_clock;

int dfs_count = 0;
int nl_count = 0;
//END DEBUG

double alphabeta_dfs(move_node & board, const int & depth, double alpha, double beta, const bool & max, const bool & red, const double & cuttoff){
    // dfs_count++;
    auto b = steady_clock::now();
    

    board.make_kids(red);
    

    if(depth == 0 || board.get_kids().size() <= 0 || (cuttoff+(std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000)) >= 13.2)
        return board.get_score();
    
    if(max){
        double r_score = -10000;
        for(auto & i : board.get_kids()){
            auto temp = alphabeta_dfs(*i, depth-1, alpha, beta, false, !red, (cuttoff+(std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000)));
            if(temp > r_score)
                r_score = temp;
            if(r_score > alpha)
                alpha = r_score;
            if(beta <= alpha || (cuttoff+(std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000)) >= 13.0)
                break;
        }
        return r_score;
    }else{
        double r_score = 10000;
        for(auto & i : board.get_kids()){
            auto temp = alphabeta_dfs(*i, depth-1, alpha, beta, true, !red, (cuttoff+(std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000)));
            if(temp < r_score)
                r_score = temp;
            if(r_score < beta)
                beta = r_score;
            if(beta <= alpha || (cuttoff+(std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000)) >= 13.0)
                break;
        }
        return r_score;
    }
}

void alphabeta_id(move_node & board, const bool & red){
    // nl_count++;
    auto b = steady_clock::now();
    int depth = 1;
    board.make_kids(red);
   
    if(board.get_kids().size() <= 1)
        return;
    do{
        for(auto & i : board.get_kids()){
            auto temp = alphabeta_dfs(*i,depth,-10000, 10000, true, red, (std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000));
            if( temp > i->get_score())
                i->set_score(temp);
        }
        depth++;
    }while((std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000) <= 13.3);
    // cout << "depth: " << depth << endl;
}



// string minimax(const string & board_start, neuralNet & net, const bool & red){
//     auto b = steady_clock::now();
//     move_node head(board_start, net);
//     head.make_kids(red);
   
//     if(head.get_kids().size() == 1){
//         auto e = steady_clock::now();
//         auto diff = e - b;
//         cout << "DF: " << head.get_kids()[0]->get_current() <<" "<< head.get_kids()[0]->get_score() <<" "<< dfs_count << " " << std::chrono::duration<double>(diff).count() << endl;
//         return head.get_kids()[0]->get_current();
//     }
//     if(head.get_kids().size() <= 0){
//         auto e = steady_clock::now();
//         auto diff = e - b;
//         cout << "DF: end "<< dfs_count << " " << std::chrono::duration<double>(diff).count() << endl;
//         return "end";
//     }
        
//     for(auto & i : head.get_kids())
//         i->set_score(alphabeta_dfs(*i, 4, -10000, 10000, true, !red, (std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000)));
 
//     head.sort_kids();
    
//     // auto e = steady_clock::now();
//     // auto diff = e - b;
    
//     // cout << "DF: " << head.get_kids()[0]->get_current() <<" "<< head.get_kids()[0]->get_score() <<" "<< dfs_count << " " << std::chrono::duration<double>(diff).count() << endl;
//     // dfs_count = 0;
//     return head.get_kids()[0]->get_current();
// }

string minimax(const string & board_start, neuralNet & net, const bool & red){
    auto b = steady_clock::now();
    move_node head(board_start, net);
        
    alphabeta_id(head,red);
    
    if(head.get_kids().size() <= 0){
        auto e = steady_clock::now();
        auto diff = e - b;
        cout << "NL: end "<< nl_count+dfs_count << " " << std::chrono::duration<double>(diff).count() << endl;
        return "end";
    }
        
    head.sort_kids();
    // auto e = steady_clock::now();
    // auto diff = e - b;
 
    // cout << "ID: " << head.get_kids()[0]->get_current()<<" "<< head.get_kids()[0]->get_score()  << " "<< nl_count+dfs_count << " " << std::chrono::duration<double>(diff).count() << endl;
    // nl_count = 0;
    // dfs_count = 0;
    return head.get_kids()[0]->get_current();
}
