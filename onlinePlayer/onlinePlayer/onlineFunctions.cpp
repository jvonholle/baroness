//
//  onlineFunctions.cpp
//  onlinePlayer
//
//  Created by BOB on 4/14/16.
//  Copyright (c) 2016 nick. All rights reserved.
//

#include "onlineFunctions.h"

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
        std::string server="skynet.cs.uaf.edu";
        std::string game_name="test";
        skynet::checkers::board_t board("rrrrrrrrr_rr_r______bbbbbbbbbbbb");
        
        std::cout<<"Playing "<<board<<" on server "<<server<<" for game "<<game_name<<":"<<std::endl;
        skynet::checkers::play_game(server,game_name,board);
        std::cout<<"Done"<<std::endl;
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

void loop(std::map<std::string,std::string> info, neuralNet * net)
{
    char buff = 'n';
    
    std::cout <<"Welcome to checkers online player!" <<std::endl;
    if(net==nullptr)
    {
        get(info["nnpath"], "nnPath");
        
        std::cout<<"net not loaded" <<std::endl;
        //LOADNET(info["nnPath"],net);
    }
    
    get(info["server"],"server");
    listGames(info["server"]);
    get(info["game"],"game");
    get(info["team"],"team");
    
    fetchGameInfo(info);
    
    std::cout <<info["curBoard"] <<" ggg"<<std::endl;
    
    std::cout <<"Another game? [Y continue] :";
    std::cin >> buff;
    if(buff=='y'||buff=='Y')
        loop(info,net);
    
    
    
    std::cout <<"BYE!" <<std::endl;
}
