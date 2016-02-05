#include "movecheck.h"
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

//check space
//will return true if pos is empty in cc
bool cSpace(const string & cs, int pos)
{
    if(cs[pos]=='_')
        return true;
    return false;
}

bool jC(const string & jc, int pos, int sel)
{
    if(sel==0)
        if(jc[checkMap(pos).first.first]!=jc[pos]&&cSpace(jc,checkMap(checkMap(pos).first.first).first.first))
            return true;
    
    if(sel==1)
        if(jc[checkMap(pos).first.second]!=jc[pos]&&cSpace(jc,checkMap(checkMap(pos).first.second).first.second))
            return true;
    
    if(sel==2)
        if(jc[checkMap(pos).second.second]!=jc[pos]&&cSpace(jc,checkMap(checkMap(pos).second.second).second.second))
            return true;
    
    if(sel==3)
        if(jc[checkMap(pos).second.first]!=jc[pos]&&cSpace(jc,checkMap(checkMap(pos).second.first).second.first))
            return true;
    
    return false;
}

//next move
//gets the next move for the board passed to it
//uses function cSpace jC and getMove
string nextMove(string orgi, int p, int sel, bool & keep, int side)
{
    if(orgi[p]=='_')
    {
        keep=false;
        return orgi;
    }
    if(side!=2)
    {
        if(sel==0)
        {
            if(cSpace(orgi,checkMap(p).first.first))
            {
                orgi[checkMap(p).first.first]='r';
                
                orgi[p]='_';
                keep=true;
            }else
            {
                if(jC(orgi,p,sel))
                {
                    orgi[checkMap(checkMap(p).first.first).first.first]=orgi[p];
                    orgi[checkMap(p).first.first]='_';
                    orgi[p]='_';
                    keep=true;
                    
                }else
                {
                    keep=false;
                }
            }
            return orgi;
        }
        
        if (sel==1)
        {
            if(cSpace(orgi,checkMap(p).first.second))
            {
                orgi[checkMap(p).first.second]=orgi[p];
                
                orgi[p]='_';
                keep=true;
            }else
            {
                if(jC(orgi,p,sel))
                {
                    orgi[checkMap(checkMap(p).first.second).first.second]=orgi[p];
                    orgi[checkMap(p).first.second]='_';
                    orgi[p]='_';
                    keep=true;
                    
                }else
                {
                    keep=false;
                }
            }
            return orgi;
        }
    }
    if(side!=1)
    {
        if (sel==2)
        {
            if(cSpace(orgi,checkMap(p).second.second))
            {
                orgi[checkMap(p).second.second]=orgi[p];
                
                orgi[p]='_';
                keep=true;
            }else
            {
                if(jC(orgi,p,sel))
                {
                    orgi[checkMap(checkMap(p).second.second).second.second]=orgi[p];
                    orgi[checkMap(p).second.second]='_';
                    orgi[p]='_';
                    keep=true;
                    
                }else
                {
                    keep=false;
                }
            }
            return orgi;
        }
        
        if(sel==3)
        {
            if(cSpace(orgi,checkMap(p).second.first))
            {
                orgi[checkMap(p).second.first]=orgi[p];
                
                orgi[p]='_';
                
                keep=true;
            }else
            {
                if(jC(orgi,p,sel))
                {
                    orgi[checkMap(checkMap(p).second.first).second.first]=orgi[p];
                    orgi[checkMap(p).second.first]='_';
                    orgi[p]='_';
                    keep=true;
                    
                }else
                {
                    keep=false;
                }
            }
            return orgi;
        }
    }

    
    return orgi;
}

//get boards
//this generates all next move boards
//right now it does both sides at once
//uses functions nextMove
void getBoards(std::vector<string> & boards)
{
    bool keep=false;
    int side;
    string temp;
    for(int i=0; i<boards[0].length();++i)
    {

        if(boards[0][i]=='r')
        {
            side=1;
        }else if(boards[0][i]=='b')
        {
            side=2;
        }
        else
        {
            side=0;
        }
        
        for(int j=0; j<4 ;++j)
        {
            
            
            temp=nextMove(boards[0],i,j,keep,side);
            if(keep)
            {
                boards.push_back(temp);
            }
            keep=false;
            
        }
    }
}


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
        
        getBoards(boards);
        
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
