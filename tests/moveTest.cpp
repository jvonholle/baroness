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

#include "../src/movement.h"



int main()
{
    int pick;
    int loop=1;
    bool quit=false;
    
    string board="rrrrrrrrrrrr________bbbbbbbbbbbb";
    
    vector<string> boards;
    
    vector<string> game;
    
    game.push_back(board);
    boards.push_back(board);
    
    while(!quit)
    {
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
    }
    
    for(int i=0; i< game.size(); ++i)
        cout << game[i] <<endl;
    
	return 0;
}
