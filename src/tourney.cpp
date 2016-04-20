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


void doublelim(vector<kaiju> & monsters){
    int print_check = 1;
    random_device d;
    mt19937 rand(d());
    std::shuffle(monsters.begin(), monsters.end(), rand);
    
    vector<int> winbracket;
    vector<int> losebracket;
    pair<int, int> gfinal;
    
    int count_up = 0;
    int count_down = monsters.size() - 1;
    
    cout << "1 for printed turns, 0 for match outcome only" << endl << "> ";
    std::cin >> print_check;
        
    cout << "starting first round!" << endl;    
    while(count_up < count_down){
        play(monsters[count_up], monsters[count_down], print_check, 200);
        play(monsters[count_down], monsters[count_up], print_check, 200);
        
        if(monsters[count_up].get_score() == monsters[count_down].get_score()){
            auto pcheck = std::uniform_int_distribution<>(0, 99);
            if(pcheck(rand)%2 == 0)
                play(monsters[count_down], monsters[count_up], print_check, 200);
            else
                play(monsters[count_up], monsters[count_down], print_check, 200);
        }
        if(monsters[count_up].get_score() > monsters[count_down].get_score()){
            winbracket.push_back(count_up);
            losebracket.push_back(count_down);
        }else{
            winbracket.push_back(count_down);
            losebracket.push_back(count_up);
        }
        
        count_up++;
        count_down--;
    }
        
    
    while(winbracket.size() > 1){
        count_up = 0;
        count_down = losebracket.size() - 1;
        
        for(int i = 0; i < monsters.size(); ++i)
            monsters[i].reset_score();
        
        vector<int> keep;
        cout << "starting losers bracket, " << losebracket.size() << " fighters" << endl;
        while(count_up < count_down){
            play(monsters[losebracket[count_up]], monsters[losebracket[count_down]], print_check, 200);
            play(monsters[losebracket[count_down]], monsters[losebracket[count_up]], print_check, 200);
            
            while(monsters[losebracket[count_up]].get_score() == monsters[losebracket[count_down]].get_score()){
                auto pcheck = std::uniform_int_distribution<>(0, 99);
                if(pcheck(rand)%2 == 0)
                    play(monsters[losebracket[count_up]], monsters[losebracket[count_down]], print_check, 200);
                else
                    play(monsters[losebracket[count_down]], monsters[losebracket[count_up]], print_check, 200);
            }
            if(monsters[losebracket[count_up]].get_score() > monsters[losebracket[count_down]].get_score())
                keep.push_back(losebracket[count_up]);
            else
                keep.push_back(losebracket[count_down]);
            
            count_up++;
            count_down--;
        }
        losebracket.clear();
        
        if(keep.size() == 1){
            gfinal.first = keep[0];
        }else{
            for(int i = 0; i < keep.size(); ++i)
                losebracket.push_back(keep[i]);
        }
            
        for(int i = 0; i < monsters.size(); ++i)
            monsters[i].reset_score();
            
        keep.clear();
        count_up = 0;
        count_down = winbracket.size() - 1;
        
        cout << "starting winner's bracket, " << winbracket.size() << " fighers" << endl;
        while(count_up < count_down){
            play(monsters[winbracket[count_up]], monsters[winbracket[count_down]], print_check, 200);
            play(monsters[winbracket[count_down]], monsters[winbracket[count_up]], print_check, 200);
            
            while(monsters[winbracket[count_up]].get_score() == monsters[winbracket[count_down]].get_score()){
               auto pcheck = std::uniform_int_distribution<>(0, 99);
                if(pcheck(rand)%2 == 0)
                    play(monsters[winbracket[count_up]], monsters[winbracket[count_down]], print_check, 200);
                else
                    play(monsters[winbracket[count_down]], monsters[winbracket[count_up]], print_check, 200);
            }
            if(monsters[winbracket[count_up]].get_score() > monsters[winbracket[count_down]].get_score()){
                keep.push_back(winbracket[count_up]);
                losebracket.push_back(winbracket[count_down]);
            }else{
                keep.push_back(winbracket[count_down]);
                losebracket.push_back(winbracket[count_up]);
            }
            count_up++;
            count_down--;
        }
        
        winbracket.clear();
        if(keep.size() == 1){
            gfinal.second = keep[0];
        }else{
            for(int i =0; i < keep.size(); ++i)
                winbracket.push_back(keep[i]);
        }
            
        keep.clear();
    }
    
    for(int i = 0; i < monsters.size(); ++i)
            monsters[i].reset_score();
    
    cout << "Grand Final! " << gfinal.first << " V " << gfinal.second << endl;
    int champ;
    play(monsters[gfinal.first], monsters[count_down], print_check, 200);
    play(monsters[gfinal.second], monsters[gfinal.first], print_check, 200);
    
    while(monsters[gfinal.first].get_score() == monsters[gfinal.second].get_score()){
       auto pcheck = std::uniform_int_distribution<>(0, 99);
        if(pcheck(rand)%2 == 0)
            play(monsters[gfinal.first], monsters[gfinal.second], print_check, 200);
        else
            play(monsters[gfinal.second], monsters[gfinal.first], print_check, 200);
    }
    if(monsters[gfinal.first].get_score() > monsters[gfinal.second].get_score())
        champ = gfinal.first;
    else
        champ = gfinal.second;
        
    cout << "done! " << champ << " is the champion, find him in kaiju/666" << endl;
    monsters[champ].evolve(666, [&](double a){return a;}, -100);
}

void doublelim(vector<neuralNet> & nets){
    int print_check;
    random_device d;
    mt19937 rand(d());
    std::shuffle(nets.begin(), nets.end(), rand);
    
    vector<int> winbracket;
    vector<int> losebracket;
    pair<int, int> gfinal;
    
    int count_up = 0;
    int count_down = nets.size() - 1;
    
    cout << "1 for printed turns, 0 for match outcome\n > ";
    std::cin >> print_check;
    while(count_up < count_down){
        play(nets[count_down], nets[count_up], print_check, 200);
        play(nets[count_up], nets[count_down], print_check, 200);
        
        if(nets[count_up].get_score() == nets[count_down].get_score()){
            auto pcheck = std::uniform_int_distribution<>(0, 99);
            if(pcheck(rand)%2 == 0)
                play(nets[count_down], nets[count_up], print_check, 200);
            else
                play(nets[count_up], nets[count_down], print_check, 200);
        }
        if(nets[count_up].get_score() > nets[count_down].get_score()){
            winbracket.push_back(count_up);
            losebracket.push_back(count_down);
        }else{
            winbracket.push_back(count_down);
            losebracket.push_back(count_up);
        }
        count_up++;
        count_down--;
    }

    while(winbracket.size() > 1){
        count_up = 0;
        count_down = losebracket.size() - 1;

        for(int i = 0; i < nets.size(); ++i)
            nets[i].reset_score();

        vector<int> keep;

        cout << "start loser bracket, " << losebracket.size() << " fighters" << endl;
        while(count_up < count_down){
            play(nets[losebracket[count_up]], nets[losebracket[count_down]], print_check, 200);
            play(nets[losebracket[count_down]], nets[losebracket[count_up]], print_check, 200);

            while(nets[losebracket[count_up]].get_score() == nets[losebracket[count_down]].get_score()){
                auto pcheck = std::uniform_int_distribution<>(0,99);
                if(pcheck(rand)%2 == 0)
                    play(nets[losebracket[count_up]], nets[losebracket[count_down]], print_check, 200);
                else
                    play(nets[losebracket[count_down]], nets[losebracket[count_up]], print_check, 200);
            }
            if(nets[losebracket[count_up]].get_score() < nets[losebracket[count_down]].get_score())
                keep.push_back(losebracket[count_down]);
            else
                keep.push_back(losebracket[count_up]);

            count_up++;
            count_down--;
        }
        losebracket.clear();

        if(keep.size() == 1){
            gfinal.first = keep[0];
        }else{
            for(int i = 0; i < keep.size(); ++i)
                losebracket.push_back(keep[i]);
        }

        for(int i = 0; i < nets.size(); ++i)
            nets[i].reset_score();

        keep.clear();
        count_up = 0;
        count_down = winbracket.size() - 1;

        cout << "start win bracket " << winbracket.size() << " fighters" << endl;
        while(count_up < count_down){
            play(nets[winbracket[count_up]], nets[winbracket[count_down]], print_check, 200);
            play(nets[winbracket[count_down]], nets[winbracket[count_up]], print_check, 200);

            while(nets[winbracket[count_up]].get_score() == nets[winbracket[count_down]].get_score()){
                auto pcheck = std::uniform_int_distribution<>(0,99);
                if(pcheck(rand)%2 == 0)
                    play(nets[winbracket[count_up]], nets[winbracket[count_down]], print_check, 200);
                else
                    play(nets[winbracket[count_down]], nets[winbracket[count_up]], print_check, 200);
            }
            if(nets[winbracket[count_up]].get_score() < nets[winbracket[count_down]].get_score()){
                keep.push_back(winbracket[count_down]);
                losebracket.push_back(winbracket[count_up]);
            }else{
                keep.push_back(winbracket[count_up]);
                losebracket.push_back(winbracket[count_down]);

            }
            count_up++;
            count_down--;
        }

        winbracket.clear();
        if(keep.size() ==1){
            gfinal.second = keep[0];
        }else{
            for(int i = 0; i < nets.size(); ++i)
                nets[i].reset_score();
        }

        keep.clear();
    }

    for(int i = 0; i < nets.size(); ++i)
        nets[i].reset_score();

    cout << "grandfinal: " << gfinal.first << " V " << gfinal.second << endl;
    int champ;
    play(nets[gfinal.first], nets[gfinal.second], print_check, 200);
    play(nets[gfinal.second], nets[gfinal.first], print_check, 200);

    while(nets[gfinal.first].get_score() == nets[gfinal.second].get_score()){
        auto pcheck = std::uniform_int_distribution<>(0,99);
        if(pcheck(rand)%2 == 0)
            play(nets[gfinal.second], nets[gfinal.first], print_check, 200);
        else
            play(nets[gfinal.first], nets[gfinal.second], print_check, 200);
    }
    if(nets[gfinal.first].get_score() > nets[gfinal.second].get_score())
        champ = gfinal.first;
    else
        champ = gfinal.second;

    cout << "champ is " << champ << endl;
    nets[champ].evolve("champ", [&](double a){return a;});
}
