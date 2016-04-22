#include "kaiju.h"
#include <iostream>
using std::cout; 
using std::endl;
#include <random>
using std::random_device;
using std::mt19937;
#include <vector>
using std::vector;
#include <utility>
using std::pair;
using std::make_pair;
#include <tuple>
using std::get;
#include <cstdlib>
using std::system;

#include <chrono>
using std::chrono::steady_clock;

kaiju::kaiju(const char & useless){
    vector<double> weights;
    random_device rd;
    mt19937 randomG(rd());
    int t_count = 0;
    auto d = std::uniform_real_distribution<> (-1,1);

    for(int i = 0; i < 4; ++i){
        weights.clear();
            for(int j = 0; j < 4060; ++j)
                weights.push_back(d(randomG));
        unique_ptr<neuralNet> temp(new neuralNet({8,40,62,20,1}, weights));
        eight_.push_back(move(temp));
    }
    for(int i = 0; i < 8; ++i){
        weights.clear();
            for(int j = 0; j < 3900; ++j)
                weights.push_back(d(randomG));
        unique_ptr<neuralNet> temp(new neuralNet({4,40,62,20,1}, weights));
        four_.push_back(move(temp));
    }
    weights.clear();
    for(int j = 0; j < 118432; ++j)
        weights.push_back(d(randomG));
    unique_ptr<neuralNet> temp(new neuralNet({16,700,111,240,12,1}, weights));
    main_ = move(temp);
    weights.clear();
    for(int j = 0; j < 10580; ++j)
        weights.push_back(d(randomG));
    unique_ptr<neuralNet> temp1(new neuralNet({32,80,80,20,1}, weights));
    head_ = move(temp1);
    weights.clear();
    for(int j = 0; j < 43842; ++j)
        weights.push_back(d(randomG));
    unique_ptr<neuralNet> temp2(new neuralNet({97,300,45,27,1}, weights));
    allinput_ = move(temp2);
}

kaiju::kaiju(const int & count){
    string path = "kaiju/";
    if(count < 10)
        path += "0";
    path += std::to_string(count);
    path += "/";
    string dir_path = path;
    
    path += "head";
    unique_ptr<neuralNet> temp(new neuralNet(path));
    head_ = move(temp);
    
    path = dir_path;
    path += "main";
    unique_ptr<neuralNet> temp1(new neuralNet(path));
    main_ = move(temp1);
    
    path = dir_path;
    path += "allinput";
    unique_ptr<neuralNet> temp2(new neuralNet(path));
    allinput_ = move(temp2);
    
    path = dir_path;
    for(int i = 0; i < 4; ++i){
        path += "eight0";
        path += std::to_string(i);
        unique_ptr<neuralNet> temp8s(new neuralNet(path));
        eight_.push_back(move(temp8s));
        path = dir_path;
    }
    
    path = dir_path;
    for(int i = 0; i < 8; ++i){
        path += "four0";
        path += std::to_string(i);
        unique_ptr<neuralNet> temp4s(new neuralNet(path));
        four_.push_back(move(temp4s));
        path = dir_path;
    }
    
}

bool kaiju::evolve(const int & count, function<double(double)> evolver, const int & cuttoff){
    if(score_ < cuttoff)
        return false;
        
    bool done = true;
    string path = "kaiju/";
    if(count < 10)
        path += "0";
    path += std::to_string(count);
    path += "/";
    string dir_path = path;
    
    do{
        done = true;
        try{
            path = dir_path;
            path += "head";
            head_->evolve(path, evolver);
            
            path = dir_path;
            path += "main";
            main_->evolve(path, evolver);
            
            path = dir_path;
            path += "allinput";
            allinput_->evolve(path, evolver);
            
            path = dir_path;
            for(int i = 0 ; i < 4; ++i){
                path += "eight0";
                path += std::to_string(i);
                eight_[i]->evolve(path, evolver);
                path = dir_path;
            }
            
            path = dir_path;
            for(int i = 0; i < 8; ++i){
                path += "four0";
                path += std::to_string(i);
                four_[i]->evolve(path, evolver);
                path = dir_path;
            }
        }catch(...){
            string dir_make = "mkdir ";
            dir_make += dir_path;
            int throwaway = system(dir_make.c_str());
            done = false;
        }
    }while(!done);

    return true;
}

pair<string, bool> kaiju::go(const string & board, bool red){
    auto b = steady_clock::now();
    move_node head(board, *head_);
    head.make_kids(red);

    if(head.get_kids().size() <= 0)
        return make_pair("end", false);
        
    if(head.get_kids().size() <= 1){
        // cout << head.get_kids()[0]->get_current() << endl;
        return make_pair(head.get_kids()[0]->get_current(), true);
    }
        
        
    for(auto & kid: head.get_kids()){
        
        vector<double> toeval;
        vector<double> allinputs;
        toeval.push_back(kid->get_score());
        
        for(int i = 0; i < 8; ++i){
            vector<double> temp;
            vector<string> eights = {"","","","","","","",""};
            
            for(int j = 0; j < 32; ++j){
                if(j < 4){
                    eights[0]+= kid->get_current()[j];
                }else if(j < 8){
                    eights[1]+= kid->get_current()[j];
                }else if(j < 12){
                    eights[2]+= kid->get_current()[j];
                }else if(j < 16){
                    eights[3]+= kid->get_current()[j];
                }else if(j < 20){
                    eights[4]+= kid->get_current()[j];
                }else if(j < 24){
                    eights[5]+= kid->get_current()[j];
                }else if(j < 28){
                    eights[6]+= kid->get_current()[j];
                }else{
                    eights[7]+= kid->get_current()[j];
                }
            }
            for(int j = 0; j < 8; ++j){
                auto doubletemp = deString(eights[j], red);
                double temptotal = 0;
                for(int i = 0; i < doubletemp.size(); ++i){
                    allinputs.push_back(doubletemp[i]);
                    temptotal+=doubletemp[i];
                }
                    
                temp.push_back(temptotal);
            }
            toeval.push_back(four_[i]->evaluate(temp));
        }
        for(int i = 0; i < 4; ++i){
            vector<double> temp;
            vector<string> fourths = {"","","",""};  
            
            for(int j = 0; j < 32; ++j){
                if(j < 8){
                    fourths[0]+= kid->get_current()[j];
                }else if(j < 16){
                    fourths[1]+= kid->get_current()[j];
                }else if(j < 24){
                    fourths[2]+= kid->get_current()[j];
                }else{
                    fourths[3]+= kid->get_current()[j];
                }
            }
            for(int j = 0; j < 4; ++j){
                auto doubletemp = deString(fourths[j], red);
                double temptotal = 0;
                for(int i = 0; i < doubletemp.size(); ++i){
                    allinputs.push_back(doubletemp[i]);
                    temptotal+=doubletemp[i];
                }
                    
                temp.push_back(temptotal);
            }
            toeval.push_back(eight_[i]->evaluate(temp));
        }
        
        auto temp = alphabeta_dfs(*kid, 4, -10000, 10000, true, red, 10);
        double tempscore = 0;
        
        for(int i = 0; i < kid->get_kids().size(); ++i)
            tempscore += kid->get_kids()[i]->get_score();
        
        kid->sort_kids();
        allinputs.push_back(tempscore);
        toeval.push_back(get<0>(temp));
        toeval.push_back(allinput_->evaluate(allinputs, 1, 2, 0));
        kid->set_score(main_->evaluate(toeval, 1, 2, 0));
    }
    head.sort_kids();
    // auto e = steady_clock::now();
    // auto diff = e-b;
    
     cout << head.get_kids()[0]->get_current();
    // if(std::chrono::duration<double>(diff).count() >= 15.0)
    //     cout << "!" << std::chrono::duration<double>(diff).count();
    // cout << endl;
    return make_pair(head.get_kids()[0]->get_current(), true);
    
}