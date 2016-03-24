#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/nnet.h"
#include <random>
using std::random_device;
using std::mt19937;
#include <algorithm>

string randboard(){
    string board = "rrrrrrrrrrrr________bbbbbbbbbbbb";
    vector<char> boardPick;
    
    for(int i = 0; i < 32; ++i)
        boardPick.push_back(board[i]);
        
    random_device rd;
    std::mt19937 gen(rd());
        
    std::shuffle(boardPick.begin(), boardPick.end(), gen);
    board = "";

    for(int i =0; i< 32; ++i)
        board+=(boardPick[i]);
    return board;
} 

TEST_CASE("Testing depth 6"){
    vector<neuralNet> nets;
    vector<double> startW;
    vector<string> boards;
    
    random_device rd;
    mt19937 randomG(rd());
    auto d = std::uniform_real_distribution<> (-1,1);
    
    for(int j = 0; j < 3700; ++j)
        startW.push_back(d(randomG));
    
    for(int i = 0; i < 100; ++i)
        nets.push_back(neuralNet({32,40,40,20,1}, startW));
    
    
    for(int i = 0; i < 1000; ++i)
        boards.push_back(randboard());
        
    for(auto & i : nets){
        for(auto j : boards){
            REQUIRE(i.go(j,true, true).first == i.go(j, true, false).first);
            REQUIRE(i.go(j,true, true).second == i.go(j, true, false).second);

            REQUIRE(i.go(j,false, true).first == i.go(j, false, false).first);
            REQUIRE(i.go(j,false, true).second == i.go(j, false, false).second);
        }
    }

}
