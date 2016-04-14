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

string rstartB(){
    random_device d;
    mt19937 rand(d());
    auto boards = getBoardsN({"rrrrrrrrrrrr________bbbbbbbbbbbb"},true);
    auto p_board = std::uniform_int_distribution<>(0, (boards.size()-1));
    boards = getBoardsN({boards[p_board(rand)]},false);
    p_board = std::uniform_int_distribution<>(0, (boards.size()-1));
    return boards[p_board(rand)];
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

        play(nets[r_net[net_i]], nets[r_net[net_j]], print_check, 200, rstartB());
       
        play(nets[r_net[net_j]], nets[r_net[net_i]], print_check, 200, rstartB());

        int temp_int = (net_i * net_j +13 / 4);
        if(temp_int % 2 == 0)
            play(nets[r_net[net_i]], nets[r_net[net_j]], print_check, 200);
        else
            play(nets[r_net[net_j]], nets[r_net[net_i]], print_check, 200);

        net_i++;
        net_j = nets.size()-(net_i+1);
    }

    int mean;
    int tot = 0;
    int off_count = 0;
    vector<neuralNet> worthy;
    path = "out";

    for(int i = 0; i < nets.size(); ++i){
        if(nets[i].get_score() >= 0){
            nets[i].evolve(path+=std::to_string(off_count), evolutionize);
            path = "out";
            worthy.push_back(nets[i]);
            off_count++;
        }
    }

    for(int i = 0; i < worthy.size(); ++i)
        tot += worthy[i].get_score();

    mean = tot / worthy.size();
    vector<neuralNet> rNets;

    for(int i = 0; i < worthy.size(); ++i)
        if(worthy[i].get_score() > mean)
            rNets.push_back(worthy[i]);

    for(int i = 0; i < rNets.size(); ++i)
        rNets[i].reset_score();

    return make_pair(off_count, rNets);
}

pair<vector<int>, vector<kaiju> > monsterfight(vector<kaiju> & monsters, const int & print_check){
    for(int i = 0; i < monsters.size(); ++i)
        monsters[i].evolve(i, [&] (double a) {return a;});
        
    vector<int> count;    
    random_device d;
    mt19937 rand(d());
    std::shuffle(monsters.begin(), monsters.end(), rand);
    
    int count_up = 0;
    int count_down = monsters.size() - 1;
    
    while(count_up < count_down){
        cout << "set: " << count_up << endl;
        play(monsters[count_up], monsters[count_down], print_check, 200, rstartB());
        play(monsters[count_down], monsters[count_up], print_check, 200 , rstartB());
        play(monsters[count_up], monsters[count_down], print_check, 200);
        play(monsters[count_down], monsters[count_up], print_check, 200);

        count_up++;
        count_down--;
    }

    for(int i = 0; i < monsters.size(); ++i)
        if(monsters[i].evolve(i, evolutionize, 1))
            count.push_back(i);

    int total = 0;
    for(int i = 0; i < count.size(); ++i)
        total += monsters[count[i]].get_score();

    int mean = total / count.size();

    vector<kaiju> worthy;
    for(int i = 0; i < count.size(); ++i)
        if(monsters[count[i]].get_score() >= mean)
            worthy.push_back(move(monsters[count[i]]));


    return make_pair(count, move(worthy));
}
