//
//  movement.cpp
//  checkers
//

#include "movement.h"
#include "movecheck.h"
#include <string>
#include <iostream>
#include <vector>

typedef pair<int,std::string> bo; // used for boards with weights

bool cSpaceN(const std::string & board, int pos)
{
    if(board[pos]!='_')
        return false;
    return true;
}

bool cJumpN(const std::string & board, int mPos, int ePos)
{
    if(checkMap(mPos).first.first == ePos)
        if(board[mPos]!=board[checkMap(mPos).first.first]&&board[checkMap(mPos).first.first]!='_')
            if(cSpaceN(board,checkMap(ePos).first.first))
                return true;
    
    if(checkMap(mPos).first.second == ePos)
        if(board[mPos]!=board[checkMap(mPos).first.second]&&board[checkMap(mPos).first.second]!='_')
            if(cSpaceN(board,checkMap(ePos).first.second))
                return true;
    
    if(checkMap(mPos).second.second == ePos)
        if(board[mPos]!=board[checkMap(mPos).second.second]&&board[checkMap(mPos).second.second]!='_')
            if(cSpaceN(board,checkMap(ePos).second.second))
                return true;
    
    if(checkMap(mPos).second.first == ePos)
        if(board[mPos]!=board[checkMap(mPos).second.first]&&board[checkMap(mPos).second.first]!='_')
            if(cSpaceN(board,checkMap(ePos).second.first))
                return true;
    
    return false;
}

std::pair<int, std::string> mBoards(std::string board,int pos, int side, int di, int score ,bool j=false)
{
    if(side!=0)
    {
        if(di==0)
        {
            if(cSpaceN(board,checkMap(pos).first.first) && !j)
            {
                board[checkMap(pos).first.first]=board[pos];
                board[pos]='_';
                score=1;
                return make_pair(score,board);
            }else if(cJumpN(board, pos, checkMap(pos).first.first))
            {
                board[checkMap(pos).first.first]='_';
                board[checkMap(checkMap(pos).first.first).first.first]=board[pos];
                board[pos]='_';
                score+=2;
                return mBoards(board, checkMap(checkMap(pos).second.first).second.first, side, di, score, true);
                
            }
        }
        if(di==1)
        {
            if(cSpaceN(board, checkMap(pos).first.second) && !j)
            {
                board[checkMap(pos).first.second]=board[pos];
                board[pos]='_';
                score=1;
                return make_pair(score,board);;
            }else if(cJumpN(board, pos, checkMap(pos).first.second))
            {
                board[checkMap(pos).first.second]='_';
                board[checkMap(checkMap(pos).first.second).first.second]=board[pos];
                score+=2;
                return mBoards(board, checkMap(checkMap(pos).second.first).second.first, side, di, score, true);
            }
        }
    }
    if(side!=1)
    {
        if(di==2)
        {
            if(cSpaceN(board, checkMap(pos).second.second) && !j)
            {
                board[checkMap(pos).second.second]=board[pos];
                board[pos]='_';
                score=1;
                return make_pair(score,board);;
            }else if(cJumpN(board, pos, checkMap(pos).second.second))
            {
                board[checkMap(pos).second.second]='_';
                board[checkMap(checkMap(pos).second.second).second.second]=board[pos];
                board[pos]='_';
                score+=2;
                return mBoards(board, checkMap(checkMap(pos).second.first).second.first, side, di, score, true);
            }
        }
        if(di==3)
        {
            if(cSpaceN(board, checkMap(pos).second.first) && !j)
            {
                board[checkMap(pos).second.first]=board[pos];
                board[pos]='_';
                score=1;
                return make_pair(score,board);
            }else if(cJumpN(board, pos, checkMap(pos).second.first))
            {
                board[checkMap(pos).second.first]='_';
                board[checkMap(checkMap(pos).second.first).second.first]=board[pos];
                board[pos]='_';
                score+=2;
                return mBoards(board, checkMap(checkMap(pos).second.first).second.first, side, di, score, true);
            }
        }
    }
    return make_pair(score,board);
}

std::vector<std::string> getBoardsN(std::vector<std::string> boards, int turn=0)
{
    std::pair<int, std::string> temp;
    temp.first= -1;
    int lim=0;
    temp.second =boards[0];
    for(int i=0; i<boards[0].length(); ++i)
    {
        if((turn==0&&(boards[0][i]=='R'||boards[0][i]=='r'))||(turn==1&&(boards[0][i]=='B'||boards[0][i]=='b'))||boards[0][i]=='_')
            continue;
        for(int j=0; j<4; ++j)
        {
            
            temp = mBoards(boards[0], i, turn, j, temp.first);
            //std::cout << temp.first <<" " <<lim <<std::endl;
            if(temp.first>=lim)
            {
                if(temp.first>lim)
                {
                    boards.erase(boards.begin()+1,boards.end());
                    lim=temp.first;
                }
                //std::cout <<"added a board" <<std::endl;
                if(!(temp.second==boards[0]))
                {
                    boards.push_back(temp.second);
                }
            }
        }
    }
    return boards;
}

