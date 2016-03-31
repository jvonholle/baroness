// #include "../src/nnet.h"
#include "../src/minimax.h"
#include <random>
using std::random_device;
using std::mt19937;
#include <algorithm>
#include <iostream>
using std::cout;
using std::endl;


string randboard(){
    string board = "rrrrrrrrrrrr________bbbbbbbbbbbb";
    // vector<char> boardPick;
    
    // for(int i = 0; i < 32; ++i)
    //     boardPick.push_back(board[i]);
        
    // random_device rd;
    // std::mt19937 gen(rd());
        
    // std::shuffle(boardPick.begin(), boardPick.end(), gen);
    // board = "";

    // for(int i =0; i< 32; ++i)
    //     board+=(boardPick[i]);
    return board;
} 

int main(){
    
    vector<double> startW;
    vector<string> game_df;
    vector<string> game_nl;
    game_df.push_back(randboard());
    game_nl.push_back(randboard());
    random_device rd;
    mt19937 randomG(rd());
    int t_count = 0;
    auto d = std::uniform_real_distribution<> (-1,1);
    
    for(int j = 0; j < 3700; ++j)
        startW.push_back(d(randomG));
    
    neuralNet red({32, 40, 40, 20, 1}, startW);
    
    startW.clear();
    for(int j = 0; j < 3700; ++j)
        startW.push_back(d(randomG));
        
        
    neuralNet black({32,40,40,20,1}, startW);
    
        
    while(t_count < 200){
        auto temp_nl = red.go(game_nl[t_count], true);

        if(temp_nl.second){
            game_nl.push_back(temp_nl.first);
            t_count++;
        }else{
            cout << "done." << endl;
            return 0;
        }
        temp_nl = black.go(game_nl[t_count], false);

        if(temp_nl.second){
            game_nl.push_back(temp_nl.first);
            t_count++;
        }else{
            cout << "done." << endl;
            return 0;
        }
    }    
}
