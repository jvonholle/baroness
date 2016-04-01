#include "tourney.h"
#include "movement.h"
#include <vector>
using std::vector;
#include <utility>
using std::pair;
using std::make_pair;
#include <random>
using std::random_device;
using std::mt19937;
using std::normal_distribution;
#include <iostream>
using std::cout;
using std::endl;
#include <chrono>
using std::chrono::steady_clock;
#include <algorithm> //for random_shuffle
#include <future>
using std::future;
using std::async;

double evolutionize(const double & W){
    random_device d;
    mt19937 rand(d());
    auto signorm = normal_distribution<>(1.0, .5);
    double sigma = signorm(rand);
    auto newWeight = normal_distribution<>(W, sigma);
    return newWeight(rand);
}

string rstartB(bool red, string s_board = "rrrrrrrrrrrr________bbbbbbbbbbbb"){
    random_device d;
    mt19937 rand(d());
    auto boards = getBoardsN({s_board},red);
    auto p_board = std::uniform_int_distribution<>(0, (boards.size()-1));
    return(boards[p_board(rand)]);
}


pair<int, vector<neuralNet> > single(vector<neuralNet> & nets, const int & gen, const int & print_check){
    string path = "current/";
    for(int i = 0; i < nets.size(); ++i){
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
        nets[i].evolve(path, [&] (double a) {return a;});
    } 

    vector<pair<int, neuralNet> > playedBoards;
    int net_i = 0;
    int net_j = nets.size()-1;
    vector<int> r_net;
    for(int i = 0; i < nets.size(); ++i) r_net.push_back(i);
    random_device d;
    mt19937 rand(d());
    std::shuffle(r_net.begin(), r_net.end(), rand);
    auto b = steady_clock::now();
    auto e = steady_clock::now();
    auto diff = e - b;

    while(net_i < net_j){
        string temp = rstartB(false);
        temp = rstartB(true, temp); 


//        cout << r_net[net_i] << " vs " << r_net[net_j] << " ";
//        b = steady_clock::now();
        // play(nets[r_net[net_i]], nets[r_net[net_j]], print_check, 200);
//        e = steady_clock::now();
//        diff = e - b;
//        cout << "time: " << std::chrono::duration<double>(diff).count() << endl;

//        cout << r_net[net_j] << " vs " << r_net[net_i] << " ";
//        b = steady_clock::now();
        // play(nets[r_net[net_j]], nets[r_net[net_i]], print_check, 200);
//        e = steady_clock::now();
//        diff = e - b;
//        cout << "time: " << std::chrono::duration<double>(diff).count() << endl;
        

//        cout << r_net[net_i] << " vs " << r_net[net_j] << " ";
//        b = steady_clock::now();
        play(nets[r_net[net_i]], nets[r_net[net_j]], print_check, 200, temp);
//        e = steady_clock::now();
//        diff = e - b;
//        cout << "time: " << std::chrono::duration<double>(diff).count() << endl;
       
        
//        cout << r_net[net_j] << " vs " << r_net[net_i] << " ";
//        b = steady_clock::now();
        play(nets[r_net[net_j]], nets[r_net[net_i]], print_check, 200, temp);
//        e = steady_clock::now();
//        diff = e - b;
//        cout << "time: " << std::chrono::duration<double>(diff).count() << endl;

//        cout << r_net[net_i] << " vs " << r_net[net_j] << " ";
//        b = steady_clock::now();
        int temp_int = (net_i * net_j +13 / 4);
        if(temp_int % 2 == 0)
            play(nets[r_net[net_i]], nets[r_net[net_j]], print_check, 200);
        else
            play(nets[r_net[net_j]], nets[r_net[net_i]], print_check, 200);
//        e = steady_clock::now();
//        diff = e - b;
//        cout << "time: " << std::chrono::duration<double>(diff).count() << endl;
        net_i++;
        net_j = nets.size()-(net_i+1);
    }

    int kids = 0;
    int mean;
    int tot = 0;
    int pc = 0;
    vector<neuralNet> worthy;
    path = "out";

    for(int i = 0; i < playedBoards.size(); ++i){
        if(nets[i].get_score() > 0){
            playedBoards[i].second.evolve(path+=std::to_string(pc), evolutionize);
            path = "out";
            worthy.push_back(nets[i]);
            kids++;
            pc++;
        }
    }

    for(int i = 0; i < worthy.size(); ++i)
        tot += worthy[i].get_score();

    mean = tot / worthy.size();
    vector<neuralNet> rNets;

    for(int i = 0; i < worthy.size(); ++i)
        if(worthy[i].get_score() > mean)
            rNets.push_back(worthy[i]);

    return make_pair(kids, rNets);
}
