#include "nnet.h"
#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <random>
using std::normal_distribution;
using std::random_device;
#include <string>
using std::string;
#include <chrono>
using std::chrono::steady_clock;
#include <map>
using std::map;

vector<double> deString(string board){
    vector<double> rVec;
    for(size_t i = 0; i < 32; ++i)
       rVec.push_back(board[i]);
   return rVec;
}

string randboard(){
    string board;
    map<int, char> boardPick;
    boardPick[0]='_';
    boardPick[1]='r';
    boardPick[2]='R';
    boardPick[3]='b';
    boardPick[4]='B';

    random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0,4);

    for(int i =0; i< 32; ++i)
        board+=(boardPick[dis(gen)]);
    return board;
} 

int main(){
    vector<double> blondieTestWeights;
    vector<string> testboards;
    random_device rd;
    std::mt19937 ranGen(rd());
    normal_distribution<> d(0,1);
    
    for(size_t i = 0; i < 1168; ++i)
        blondieTestWeights.push_back(d(ranGen));

    for(size_t i = 0; i < 1000000; ++i)
        testboards.push_back(randboard());

    neuralNet tester({32,24,16,1}, blondieTestWeights);

    auto b = steady_clock::now();
    for(size_t i = 0; i< testboards.size(); ++i)
        tester.evaluate(deString(testboards[i]));
    auto e = steady_clock::now();
    auto diff = e-b;
    cout << "time: " << std::chrono::duration<double>(diff).count() << endl;
}
