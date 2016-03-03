#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <vector>
using std::vector;
#include<string>
using std::string;
#include <utility>
using std::pair;
#include <stdexcept>

#include <time.h>
#include <cstdlib>

//#include "checkers.hpp"
//#include "checkers_client.hpp"

#include "movement.h"

typedef pair<int,string> bo;
//
////needs skynet
////
//bool send(string b)
//{
//    try
//    {
//        std::string server="127.0.0.1:8080";
//        std::string game_name="t2";
//        skynet::checkers::board_t board(b.c_str());
//        
//        std::cout<<"Playing "<<board<<" on server "<<server<<" for game "<<game_name<<":"<<std::endl;
//        
//        skynet::checkers::play_game(server,game_name,board);
//        
//        std::cout<<"Done"<<std::endl;
//    }
//    catch(std::exception& error)
//    {
//        std::cout<<"Error - "<<error.what()<<std::endl;
//    }
//    catch(...)
//    {
//        std::cout<<"Error - Unknown."<<std::endl;
//    }
//    
//    return false;
//}
//
//
//
int main()
{
    //bool quit=false;
    string buff;
    int loop=2;
    bo board;
    board.second="rrrrrrrrrrr____r____bbbbbbbbbbbb";
    board.first=0;
    
    vector<bo> boards;
    
    vector<string> game;
    
    game.push_back(board.second);
    boards.push_back(board);
        
    boards = getBoardsN(boards, loop%2);
    
    for(int i=1; i<boards.size(); ++i)
    {
        cout<<i <<" "<<boards[i].first <<" : " <<boards[i].second <<endl;
        //cout<<boards[i].second <<endl;
    }
    cout <<"done" <<endl;
//    while(!quit)
//    {
//        cin >> buff;
//        if(buff=="0")
//        {
//            quit=true;
//        }
//    }
    
	return 0;
}
