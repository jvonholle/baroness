//
//  main.cpp
//  onlinePlayer
//


#include <ctime>
#include <string>
#include <iostream>
#include <stdexcept>
#include "skynet/checkers.hpp"
#include "skynet/checkers_client.hpp"
#include <map>
#include "nnet.h"
#include "kaiju.h"

void print_time(const uint64_t milliseconds)
{
    time_t time=milliseconds/1000;
    std::cout<<std::asctime(std::localtime(&time))<<std::flush;
}

void print_game(const std::string& game_name,const skynet::checkers::game_info_t& game_info)
{
    std::cout<<"  Name     "<<game_name<<std::endl;
    std::cout<<"  Status   "<<std::to_string(game_info.status)<<std::endl;
    std::cout<<"  Boards   "<<game_info.boards.size()<<std::endl;
    
    for(auto board:game_info.boards)
        std::cout<<"    "<<board<<std::endl;
    
    std::cout<<"  Created  "<<std::flush;
    print_time(game_info.create_time);
    std::cout<<"  Modified "<<std::flush;
    print_time(game_info.modify_time);
}

void listGames(std::string server)
{
    try
    {
        std::cout<<"Listing games on server "<<server<<":"<<std::endl;
        
        for(auto game:skynet::checkers::list_games(server))
            print_game(game.first,game.second);
    }
    catch(std::exception& error)
    {
        std::cout<<"Error - "<<error.what()<<std::endl;
    }
    catch(...)
    {
        std::cout<<"Error - Unknown."<<std::endl;
    }
    
}

void fetchGameInfo(std::map<std::string, std::string>& info)
{
    try
    {
        auto game = skynet::checkers::info_game(info["server"], info["game"]);
        info["curTurn"]= std::to_string(game.status);
        for(auto board:game.boards)
            info["curBoard"] = board;
    }
    catch(std::exception& error)
    {
        std::cout<<"Error - "<<error.what()<<std::endl;
        info["server"]="";
    }
    catch(...)
    {
        std::cout<<"Error - Unknown."<<std::endl;
    }
}

void move(std::string server, std::string game, std::string board)
{
    try
    {
        std::cout<<"Playing "<<board<<" on server "<<server<<" for game "<<game<<":"<<std::endl;
        skynet::checkers::play_game(server,game,board);
        //std::cout<<"Done"<<std::endl;
    }
    catch(std::exception& error)
    {
        std::cout<<"Error - "<<error.what()<<std::endl;
        
    }
    catch(...)
    {
        std::cout<<"Error - Unknown."<<std::endl;
    }
}

void caseCheck(std::string & c, int opt)
{
    if(opt==1)
    {
        if(c=="r")
            c="R";
        else if(c=="b")
            c="B";
    }
}

bool get(std::string & data, std::string opt)
{
    char ans='n';
    if(data!="")
    {
        if(opt=="team")
        {
            caseCheck(data,1);
        }
        std::cout <<"Is " <<data <<" the correct "<<opt <<"? [Y,N]" <<std::endl;
        std::cin >> ans;
        if(ans == 'y' || ans == 'Y')
            return true;
    }
    if(opt == "team")
    {
        std::cout <<"[R/B] ";
    }
    std::cout <<"Enter "<<opt <<":";
    std::cin >> data;
    
    return get(data,opt);
}

void LOADNET(std::string path, neuralNet * net)
{
    net = new neuralNet(path);
}

bool won(std::map<std::string,std::string> &info)
{
    std::string tmp = info["curTurn"];
    if (tmp.find("won") != std::string::npos) {
        return true;
    }
    
    return false;
}

void playLoop(std::map<std::string,std::string> info, neuralNet & net, kaiju & kaij, bool kon)
{
    bool w=true;
    bool over = false;
    bool red;
    std::string nextMove, curBoard;
    
    if(info["team"]=="R")
    {
        red = true;
    }else{
        red = false;
    }
    
    std::cout <<"Playing" <<std::endl;
    while(!over)
    {
        fetchGameInfo(info);
        if(info["server"]=="")
            break;
        
        curBoard=info["curBoard"];
        //std::cout <<info["team"] <<" " <<info["curTurn"] <<std::endl;
        if("red_turn" == info["curTurn"] && red)
        {
            std::cout <<"moveGen" <<std::endl;
            if(kon)
            {
                nextMove = kaij.go(curBoard,red).first;
            }
            else
            {
                nextMove = net.go(curBoard,red).first;
            }
            
            fetchGameInfo(info);
            
            if("red_turn" == info["curTurn"])
            {
                //std::cout <<"move :" <<nextMove;
                move(info["server"],info["game"], nextMove);
                std::cout <<"Move sent" <<std::endl;
            }else
            {
                std::cout <<"someone may have moved for you!" <<std::endl;
            }
            
            w=true;
        
        }else if ("black_turn" == info["curTurn"] && !red)
        {
            std::cout <<"moveGen" <<std::endl;
            if(kon)
            {
                nextMove = kaij.go(curBoard,red).first;
            }
            else
            {
                nextMove = net.go(curBoard,red).first;
            }
            
            if("black_turn" == info["curTurn"])
            {
                //std::cout <<"move :" <<nextMove;
                move(info["server"],info["game"], nextMove);
                std::cout <<"Move sent" <<std::endl;
            }else
            {
                std::cout <<"someone may have moved for you!" <<std::endl;
            }
            
            w=true;
        }
        else if(won(info))
        {
            std::cout << " GAME OVER !\n" <<info["curTurn"] <<std::endl;
            over=true;
        }else
        {
            
            if(w)
                std::cout<<"waiting" <<std::endl;
            
            w=false;
            
        }
    
    }
}

void loop(std::map<std::string,std::string> info, neuralNet & net, kaiju & kaij, bool kon)
{
    char buff = 'n';
    bool quit=false;
    while(!quit)
    {
    //get(info["nnPath"], "nnPath");
    //std::cout<<"net not loaded" <<std::endl;
    //LOADNET(info["nnPath"],net);
    
    get(info["server"],"server");
    listGames(info["server"]);
    get(info["game"],"game");
    get(info["team"],"team");
    
    fetchGameInfo(info);
    
   // std::cout <<info["curBoard"] <<" "<<info["curTurn"] <<" ggg"<<std::endl;
    
    
    playLoop(info, net, kaij, kon);
    
    
    
    //END
    std::cout <<"Another game? [Y continue] :";
    std::cin >> buff;
    if(buff=='n'||buff=='N')
        quit = true;
    }
    std::cout <<"BYE!" <<std::endl;
}



bool kaijuOrNah()
{
    char b;
    std::cout << "Are you useing a kaiju? [Y/N] :";
    std::cin >> b;
    if(b=='y'||b=='Y')
    {
        return true;
    }
    return false;
}

//
//Game function
//
int main()
{
    std::map<std::string,std::string> info;
    info["server"]="skynet.cs.uaf.edu";
    info["game"]="TEST";
    info["team"]="R";
    info["board"]="";
    info["nnPath"]="random_nnet.txt";
    info["curTurn"]="";
    info["curBoard"]="";
    bool k=false;
    neuralNet net;
    kaiju tresspasser('g');
    //Start
    std::cout <<"Welcome to checkers online player!" <<std::endl;
    k = kaijuOrNah();
    if(!k)
    {
        get(info["nnPath"], "nnPath");
    }
    if(!k)
    {
        net = neuralNet(info["nnPath"]);
    }else
    {
        std::cout <<"random kaiju? [Y/N] :";
        char t;
        std::cin >>t;
        if(t=='N'||t=='n')
        {
            int kju;
            std::cout <<"not rand enter k# :" ;
            std::cin >> kju;
            tresspasser = kaiju(kju);
        }
        
    }
    
    std::cout <<"net loaded" <<std::endl;
    loop(info,net,tresspasser,k);
    
    return 0;
}