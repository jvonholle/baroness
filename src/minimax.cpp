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

tuple<double, double, double> alphabeta_dfs(move_node & board, const int & depth, double alpha, double beta, const bool & max, const bool & red, const double & cuttoff){
    dfs_count++;
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

void alphabeta_id(move_node & board, const bool & red){
    nl_count++;
    auto b = steady_clock::now();
    int depth = 1;
    double timec = (std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000.0);
    board.make_kids(red);
    double turnt =0;
   
    if(board.get_kids().size() <= 1)
        return;
    
    do{
        timec = (std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000.0);
        turnt = timec;
        
        auto temp = alphabeta_dfs(*board.get_kids()[0], depth, -10000, 10000, true, red, (13.5-timec));
        board.get_kids()[0]->set_score(get<0>(temp));
        
        timec = (std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000.0);
        turnt = timec - turnt;
        
        for(int i = 1; i < board.get_kids().size(); ++i){
            timec = (std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000.0);
            if(timec+turnt >= 14.7)
                break;
            turnt = timec;
            temp = alphabeta_dfs(*board.get_kids()[i], depth, get<1>(temp), get<2>(temp), true, red, (13.5-timec));
            board.get_kids()[i]->set_score(get<0>(temp));
            
            timec = (std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000.0);
            turnt = timec - turnt;
            if(timec >= 14.7)
                break;
        }
        depth++;
        timec = (std::chrono::duration_cast<std::chrono::milliseconds>(steady_clock::now()-b).count()/1000.0);
    }while(timec+turnt <= 14.6);
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
    auto e = steady_clock::now();
    auto diff = e - b;
 
    cout << head.get_kids()[0]->get_current(); 
    if(std::chrono::duration<double>(diff).count() >= 15.0)
        cout << "!";
    cout << endl;
    nl_count = 0;
    dfs_count = 0;
    return head.get_kids()[0]->get_current();
}
