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

void save(vector<neuralNet> & nets){
    string path = "saved/";
    for(int i = 0; i < nets.size(); ++i){
        path = "saved/";
        if(i < 10){
            path += "net_00";
            path += std::to_string(i);
        }else if(i < 100 && i >= 10){
            path += "net_0";
            path += std::to_string(i);
        }else{
            path += "net_";
            path += std::to_string(i);
        }
        nets[i].evolve(path, [&] (double a) {return a;});
    }
}

void load(vector<neuralNet> & nets, const int & check, const int & quant){
    int count = 0;
    if(check == 3){
        string path = "saved/";
        for(int i = 0; i < quant; ++i){
            path = "saved/";
            if(i < 10){
                path += "net_00";
                path += std::to_string(i);
            }else if(i < 100 && i >= 10){
                path += "net_0";
                path += std::to_string(i);
            }else{
                path += "net_";
                path += std::to_string(i);
            }
            nets.push_back(neuralNet(path));
            count++;
        }
        cout << "loaded " << count << " nets" << endl;
        return;
    }
    if(check == 4){
        string path = "current/";
        for(int i = 0; i < quant; ++i){
            path = "current/";
            if(i < 10){
                path += "net_00";
                path += std::to_string(i);
            }else if(i < 100 && i >= 10){
                path += "net_0";
                path += std::to_string(i);
            }else{
                path += "net_";
                path += std::to_string(i);
            }
            count++;
            nets.push_back(neuralNet(path));
        }
        cout << "loaded " << count << " nets" << endl;
    }
}

int main(){
    vector<neuralNet> nets;
    vector<double> startW;
    string filepath = "out";
    random_device rd;
    mt19937 randomG(rd());
    size_t gen = 0; 
    int check;
    int num_nets;
    auto d = std::uniform_real_distribution<> (-1,1);

    cout << "1 for new random gen, 3 to load last saved, 4 to load last used gen" << endl << "> ";
    std::cin >> check;
    if(check == 3 || check == 4){
        cout << "how many nets to load? if not sure use 100" << endl << "> ";
        std::cin >> num_nets;
        load(nets, check, num_nets);
    }else{ 
        for(int i = 0; i < 100; ++i){
            startW.clear();
            randomG.seed(rd());
            for(int j = 0; j < 3700; ++j)
                startW.push_back(d(randomG));
            nets.push_back(neuralNet({32,40,40,20,1}, startW));
        }
        cout << "done random gen" << endl;
    }

    cout << "1 for printed turns, 0 for match outcome only" << endl << "> ";
    std::cin >> check;

    auto b = steady_clock::now();

    auto count = single(nets, -1, check); 
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
        count = single(nets, gen, check);
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
