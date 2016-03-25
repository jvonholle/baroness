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
    vector<string> game;
    game.push_back(randboard());
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
    string mm = "mm";
    string ab = "ab";
    string dfs = "dfs";
    
        
    while(t_count < 200){
        
        auto temp_mm = red.go(game[t_count], true, mm);
        auto temp_ab = red.go(game[t_count], true, ab);
        auto temp_df = red.go(game[t_count], true, dfs);

        if(temp_mm.second && temp_ab.second){
            game.push_back(temp_ab.first);
            t_count++;
        }else{
            return 0;
        }
        
        temp_mm = black.go(game[t_count], false, mm);
        temp_ab = black.go(game[t_count], false, ab);
        temp_df = black.go(game[t_count], false, dfs);

        if(temp_mm.second && temp_ab.second){
            game.push_back(temp_ab.first);
            t_count++;
        }else{
            return 0;
        }
    }    
}
