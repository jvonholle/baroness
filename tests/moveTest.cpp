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

<<<<<<< HEAD
#include <time.h>
#include <cstdlib>
=======
#include "movement.h"
>>>>>>> 1cde3bb1466557a51f18ca6f0bd106d8da41f8b6

//#include "checkers.hpp"
//#include "checkers_client.hpp"

#include "../src/movement.h"

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
<<<<<<< HEAD
        cout<<i <<" "<<boards[i].first <<" : " <<boards[i].second <<endl;
        //cout<<boards[i].second <<endl;
=======
        boards = getBoardsN(boards, loop%2);
        cout<< "First: " <<boards[0] <<endl;
        for(int i=1;i<boards.size(); ++i)
            cout<<boards[i] <<endl;
        cout <<boards.size()-1 <<endl;
        
        cout<<" pick an index or 0 to quit" <<endl;
        
        
        cin >> pick;
        if(pick>boards.size()||pick<=0)
        {
            quit=true;
        }else{
            board = boards[pick];
            boards.clear();
            boards.push_back(board);
            game.push_back(board);
        }
        
        ++loop;
>>>>>>> 1cde3bb1466557a51f18ca6f0bd106d8da41f8b6
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
