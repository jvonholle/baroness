//
//  onlineFunctions.h
//  onlinePlayer
//
//  Created by BOB on 4/14/16.
//  Copyright (c) 2016 nick. All rights reserved.
//

#ifndef __onlinePlayer__onlineFunctions__
#define __onlinePlayer__onlineFunctions__


#include <ctime>
#include <string>
#include <iostream>
#include <stdexcept>
#include "skynet/checkers.hpp"
#include "skynet/checkers_client.hpp"
#include <map>
#include "nnet.h"


void print_time(const uint64_t milliseconds);

void print_game(const std::string& game_name,const skynet::checkers::game_info_t& game_info);

void listGames(std::string server);

void fetchGameInfo(std::map<std::string, std::string>& info);

void move(std::string server, std::string game, std::string board);

void caseCheck(std::string & c, int opt);

bool get(std::string & data, std::string opt);

void LOADNET(std::string path, neuralNet * net);

void loop(std::map<std::string,std::string> info, neuralNet * net);

#endif /* defined(__onlinePlayer__onlineFunctions__) */
