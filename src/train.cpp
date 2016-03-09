#include "tourney.h"
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <utility>
using std::pair;
using std::make_pair;
#include <random>
using std::random_device;
using std::mt19937;
using std::normal_distribution;
#include <chrono>
using std::chrono::steady_clock;
#include <cstddef>
using std::size_t;
#include <iostream>
using std::cout;
using std::endl;

int main(){
    vector<neuralNet> nets;
    vector<double> startW;
    string filepath = "out";
    random_device rd;
    mt19937 randomG(rd());
    size_t gen = 0; 
    auto d = normal_distribution<> (0,.9);
    cout << "start random gen" << endl;
    for(int i = 0; i < 100; ++i){
        startW.clear();
        for(int j = 0; j < 3700; ++j)
            startW.push_back(d(randomG));
        nets.push_back(neuralNet({32,40,40,20,1}, startW));
    }
    cout << "done random gen" << endl;
    auto b = steady_clock::now();
    cout << "starting gen -1 tourney" << endl;
    auto count = roundrobin(nets); 
    auto e = steady_clock::now();
    auto diff = e - b;
    cout << "gen: " << -1 << endl
        << "time: " << std::chrono::duration<double>(diff).count() << " seconds" << endl
        << "offspring: " << count.first << endl
        << "survivors: " << count.second.size() << endl;
    while(true){
        b = steady_clock::now();
        nets.clear();
        for(auto& i : count.second)
            nets.push_back(i);
        for(int i = 0; i < count.first; ++i){
            nets.push_back(neuralNet(filepath+=std::to_string(i)));
            filepath = "out";
        }
        if(nets.size() < 100){
            int temp = 100 - nets.size();
            for(int i = 0; i < temp; ++i){
                startW.clear();
                for(int j = 0; j < 3700; ++j)
                    startW.push_back(d(randomG));
                nets.push_back(neuralNet({32,40,40,20,1}, startW));
            }
        }
        count = roundrobin(nets);
        e = steady_clock::now();
        diff = e - b; 
        cout << "gen: " << gen << endl
            << "time: " << std::chrono::duration<double>(diff).count() << " seconds" << endl
            << "offspring: " << count.first << endl
            << "survivors: " << count.second.size() << endl;
        gen++;
    }
    return 0;
}
