#include "player.h"

#include <utility>
using std::pair;
using std::make_pair;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;
#include <chrono>
using std::chrono::steady_clock;


int p_count(string board, char turn){
    int count = 0;
    for(int i = 0; i < 32; ++i)
        if(board[i] == turn || board[i] == turn-32)
            count++;
    return count;
}


void play(neuralNet & red, neuralNet & black,int pc, const int turns, const string startB){
    int t_count = 0;
    auto b = steady_clock::now();
    auto e = steady_clock::now();
    auto diff = e - b;
    vector<double> t_times;
    double avg_t;
    vector<string> game;
    game.clear(); 
    game.push_back(startB);
    int too_long = 0;
    
    while(t_count < turns){
        
        b = steady_clock::now();
        
        auto temp = red.go(game[t_count], true);

            e = steady_clock::now();
            diff = e - b;
            t_times.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(diff).count()/1000.0);
        
        if(temp.second){
            game.push_back(temp.first);
            t_count++;
            //cout << "red move:" << endl;
            if(pc == 1)
                cout << game[t_count] << " " << t_times[t_count-1] << " sec" << endl;
        }else{
            if(pc == 0 || pc == 1){
                for(int i = 0; i<t_times.size(); ++i){
                    avg_t+= t_times[i];
                    if(t_times[i]>15.0)
                        too_long++;
                }
                avg_t = avg_t/t_times.size();
            
                cout << "black wins, average turn time: " << avg_t << " with: " << too_long << " over 15 seconds" << endl;
            }
            black.set_score(3);
            red.set_score(-3);
            return;
        }
        
        b = steady_clock::now();
        
        temp = black.go(game[t_count], false);
        
        e = steady_clock::now();
        diff = e - b;
        t_times.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(diff).count()/1000.0);
        
        if(temp.second){
            game.push_back(temp.first);
            t_count++;
            //cout << "black move:" << endl;
            if(pc == 1){
                cout << game[t_count] << " " << t_times[t_count-1] << " sec" << endl;
            }
        }else{
            if(pc == 0 || pc == 1){
                for(int i = 0; i<t_times.size(); ++i){
                    avg_t+= t_times[i];
                    if(t_times[i] > 15.0)
                        too_long++;
                }
                avg_t = avg_t/t_times.size();
                cout << "red wins, average turn time: " << avg_t << " with: " << too_long << " over 15 seconds " << endl;
            }
            black.set_score(-3);
            red.set_score(3);
            return;
        }
    }
    if(pc == 0){
        for(int i = 0; i<t_times.size(); ++i)
            avg_t+= t_times[i];
        avg_t = avg_t/t_times.size();
        cout << "draw! average turn time: " << avg_t << " ";
    }
    
    black.set_score(-1);
    red.set_score(-1);

    return;
}
