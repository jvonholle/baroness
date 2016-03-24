#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/nnet.h"
#include <random>
using std::random_device;
using std::mt19937;
#include <algorithm>

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

TEST_CASE("Testing depth 6"){
    
    vector<double> startW;
    vector<string> boards;
    
    random_device rd;
    mt19937 randomG(rd());
    auto d = std::uniform_real_distribution<> (-1,1);
    
    for(int j = 0; j < 3700; ++j)
        startW.push_back(d(randomG));
    
    neuralNet red();
    
    for(int j = 0; j < 3700; ++j)
        startW.push_back(d(randomG));
        
        
    neuralNet black;
    
    for(int i = 0; i < 100; ++i)
        boards.push_back(randboard());
        
    while(t_count < 200){
        auto temp_mm = red.go(game[t_count], true, false);
        auto temp_ab = red.go(game[t_count], true, true);        
        REQUIRE(temp_mm.first == temp_ab.first);
        REQUIRE(temp_mm.second == temp_ab.second);

        if(temp_mm.second && temp_ab.second){
            game.push_back(temp.first);
            t_count++;
        }else{
            break;
        }

        
        temp_mm = black.go(game[t_count], true, false);
        temp_ab = black.go(game[t_count], true, true);        
        REQUIRE(temp_mm.first == temp_ab.first);
        REQUIRE(temp_mm.second == temp_ab.second);
        
        
        if(temp_mm.second && temp_ab.second){
            game.push_back(temp.first);
            t_count++;
        }else{
            break;
        }
    }    
}

//CODE FROM PLAYER.CPP
//NEED TO TURN INTO WORKABLE CATCH STUFF

//     
