#include "tourney.h"
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

double evolutionize(const double & W){
    random_device d;
    mt19937 rand(d());
    auto signorm = normal_distribution<>(1.0, .5);
    double sigma = signorm(rand);
    auto newWeight = normal_distribution<>(W, sigma);
    return newWeight(rand);
    return W;
}

pair<int, vector<neuralNet> > roundrobin(vector<neuralNet> & nets, const int & gen, const int & print_check){
    string path = "current/";
    for(int i = 0; i < nets.size(); ++i){
        path = "current/";
        if(i < 10){
            path += "net_00";
            path += std::to_string(i);
        }else if(i < 100){
            path += "net_0";
            path += std::to_string(i);
        }else{
            path += "net_";
            path += std::to_string(i);
        }
        nets[i].evolve(path, [&] (double a) {return a;});
    } 
    int score = 0;
    auto b = steady_clock::now();
    auto e = steady_clock::now();
    auto diff = e - b;
    vector<pair<int, neuralNet> > playedBoards;
    cout << "start round robin" << endl;
    for(int i = 0; i < nets.size(); ++i){
        score = 0;
        for(int j = 0; j < nets.size(); ++j){
            if(i == j)
                continue;
            b = steady_clock::now();
            score += play(nets[i], nets[j],print_check, 200);
            if(print_check == 1)
                cout << " game #" << (i+1)*j << endl;
            e = steady_clock::now();
        }
        diff = e-b;
        cout << "net " << i << " done time: " << std::chrono::duration<double>(diff).count() << " sec" <<endl;
        playedBoards.push_back(make_pair(score, nets[i]));
    }
    int kids = 0;
    int mean;
    int tot = 0;
    int pc = 0;
    vector<pair<int, neuralNet> > worthy;
    for(int i = 0; i < playedBoards.size(); ++i){
        tot += playedBoards[i].first;
    }
    mean = tot / playedBoards.size();
    tot = 0;
    for(int i = 0; i < playedBoards.size(); ++i){
        if(playedBoards[i].first > mean){
            playedBoards[i].second.evolve(path+=std::to_string(pc), evolutionize);
            path = "out";
            worthy.push_back(playedBoards[i]);
            kids++;
            pc++;
        }
    }
    for(int i = 0; i < worthy.size(); ++i)
        tot += worthy[i].first;
    mean = tot / worthy.size();
    vector<neuralNet> rNets;
    for(int i = 0; i < worthy.size(); ++i)
        if(worthy[i].first > mean)
            rNets.push_back(worthy[i].second);

    return make_pair(kids, rNets);
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

    int score_i = 0;
    int score_j = 0;
    vector<pair<int, neuralNet> > playedBoards;
    int net_i = 0;
    int net_j = nets.size()-1;
    vector<int> r_net;
    for(int i = 0; i < 100; ++i) r_net.push_back(i);
    std::random_shuffle(r_net.begin(), r_net.end());

    while(net_i < net_j){
        cout << r_net[net_i] << " vs " << r_net[net_j] << " ";
        score_i = play(nets[r_net[net_i]], nets[r_net[net_j]], print_check, 200);
        cout << r_net[net_j] << " vs " << r_net[net_i] << " ";
        score_j = play(nets[r_net[net_j]], nets[r_net[net_i]], print_check, 200);
        playedBoards.push_back(make_pair(score_i, nets[r_net[net_i]]));
        playedBoards.push_back(make_pair(score_j, nets[r_net[net_j]]));
        net_i++;
        net_j = nets.size()-(net_i+1);
    }
             
    int kids = 0;
    int mean;
    int tot = 0;
    int pc = 0;
    vector<pair<int, neuralNet> > worthy;
    path = "out";

    for(int i = 0; i < playedBoards.size(); ++i){
        tot += playedBoards[i].first;
    }   

    mean = tot / playedBoards.size();
    tot = 0;

    for(int i = 0; i < playedBoards.size(); ++i){
        if(playedBoards[i].first > mean){
        playedBoards[i].second.evolve(path+=std::to_string(pc), evolutionize);
        path = "out";
        worthy.push_back(playedBoards[i]);
        kids++;
        pc++;
        }
    }

    for(int i = 0; i < worthy.size(); ++i)
        tot += worthy[i].first;

    mean = tot / worthy.size();
    vector<neuralNet> rNets;

    for(int i = 0; i < worthy.size(); ++i)
        if(worthy[i].first > mean)
            rNets.push_back(worthy[i].second);

    return make_pair(kids, rNets);
}
