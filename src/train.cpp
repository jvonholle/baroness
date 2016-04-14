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

void train_nets(){
    vector<neuralNet> nets;
    vector<double> startW;
    string filepath = "out";
    random_device rd;
    mt19937 randomG(rd());
    size_t gen = 0; 
    int check;
    int num_nets;
    auto d = std::uniform_real_distribution<> (-1,1);

    cout << "1 for new random gen, 4 to load last gen" << endl << "> ";
    std::cin >> check;
    if(check == 4){
        cout << "how many nets to load? if not sure use 100" << endl << "> ";
        std::cin >> num_nets;
        load(nets, check, num_nets);
    }else{ 
        for(int i = 0; i < 50; ++i){
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
        if(nets.size() < 50){
            int temp = 50 - nets.size();
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
}

void train_kaiju(){
    vector<kaiju> monsters;
    int check;
    int pop_count;
    int gen_count = 0;
    cout << "1 for new random, 0 to load" << endl << "> ";
    std::cin >> check;
    if(check == 0){
        cout << "load how many?" << endl << "> ";
        std::cin >> pop_count;
        for(int i = 0; i < pop_count; ++i)
            monsters.push_back(kaiju(i));
        cout << "done loading." << endl
             << "loaded: " << monsters.size() << endl;
    }else if(check == 1){
        cout << "make how many?" << endl << "> ";
        std::cin >> pop_count;
        for(int i = 0; i < pop_count; ++i)
            monsters.push_back(kaiju('s'));
        cout << "done random generation." << endl
             << "made: " << monsters.size() << endl;
    }else{
        cout << "that wasn't a valid number." << endl;
        return;
    }
    
    cout << "1 for printed turns, 0 for match outcome only" << endl << "> ";
    std::cin >> check;
    while(true){
        cout << "starting gen " << gen_count << endl;
        auto b = steady_clock::now();
        
        auto results = monsterfight(monsters, check);
        monsters.clear();

        monsters = move(results.second);

        cout << endl << monsters.size() << endl;

        for(int i = 0; i < results.first.size(); ++i)
            monsters.push_back(kaiju(results.first[i]));

        cout << endl << monsters.size() << endl;

        if(monsters.size() < pop_count){
           for(int i = monsters.size(); i < (pop_count); ++i)
               monsters.push_back(kaiju('s'));
        }


        cout << endl << monsters.size() << endl;

        
        auto e = steady_clock::now();
        auto diff = e - b; 
        cout << "gen: " << gen_count << " done" << endl
            << "time: " << ((std::chrono::duration<double>(diff).count()/60)/60) << " hours" << endl
            << "monsters: " << monsters.size() << endl;
        gen_count++;
    }
 return;
}

int main(){
    int check;
    cout << "1 for nets 0 for kaiju" << endl << "> ";
    std::cin >> check;
    if(check == 1)
        train_nets();
    else if(check == 0)
        train_kaiju();
    else
        return 0;
}
