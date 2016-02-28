//
//  movement.cpp
//  checkers
//

#include "movement.h"
#include <string>
#include <vector>

typedef pair<int,std::string> bo; // used for boards with weights

bool cSpaceN(const bo & board, int pos)
{
    if(board.second[pos]!='_')
        return false;
    return true;
}

bool cJumpN(const bo & board, int mPos, int ePos)
{
    if(checkMap(mPos).first.first == ePos)
        if(board.second[mPos]!=board.second[checkMap(mPos).first.first]&&board.second[checkMap(mPos).first.first]!='_')
            if(cSpaceN(board,checkMap(ePos).first.first))
                return true;
    
    if(checkMap(mPos).first.second == ePos)
        if(board.second[mPos]!=board.second[checkMap(mPos).first.second]&&board.second[checkMap(mPos).first.second]!='_')
            if(cSpaceN(board,checkMap(ePos).first.second))
                return true;
    
    if(checkMap(mPos).second.second == ePos)
        if(board.second[mPos]!=board.second[checkMap(mPos).second.second]&&board.second[checkMap(mPos).second.second]!='_')
            if(cSpaceN(board,checkMap(ePos).second.second))
                return true;
    
    if(checkMap(mPos).second.first == ePos)
        if(board.second[mPos]!=board.second[checkMap(mPos).second.first]&&board.second[checkMap(mPos).second.first]!='_')
            if(cSpaceN(board,checkMap(ePos).second.first))
                return true;
    
    return false;
}

bo mBoards(bo board,int pos, int side, int di ,bool j=false)
{
    if(side!=0)
    {
        if(di==0)
        {
            if(cSpaceN(board,checkMap(pos).first.first) && !j)
            {
                board.second[checkMap(pos).first.first]=board.second[pos];
                board.second[pos]='_';
                board.first=1;
                return board;
            }else if(cJumpN(board, pos, checkMap(pos).first.first))
            {
                board.second[checkMap(pos).first.first]='_';
                board.second[checkMap(checkMap(pos).first.first).first.first]=board.second[pos];
                board.second[pos]='_';
                board.first+=2;
                return mBoards(board, checkMap(checkMap(pos).second.first).second.first, side, di, true);
                
            }
        }
        if(di==1)
        {
            if(cSpaceN(board, checkMap(pos).first.second) && !j)
            {
                board.second[checkMap(pos).first.second]=board.second[pos];
                board.second[pos]='_';
                board.first=1;
                return board;
            }else if(cJumpN(board, pos, checkMap(pos).first.second))
            {
                board.second[checkMap(pos).first.second]='_';
                board.second[checkMap(checkMap(pos).first.second).first.second]=board.second[pos];
                board.first+=2;
                return mBoards(board, checkMap(checkMap(pos).second.first).second.first, side, di, true);
            }
        }
    }
    if(side!=1)
    {
        if(di==2)
        {
            if(cSpaceN(board, checkMap(pos).second.second) && !j)
            {
                board.second[checkMap(pos).second.second]=board.second[pos];
                board.second[pos]='_';
                board.first=1;
                return board;
            }else if(cJumpN(board, pos, checkMap(pos).second.second))
            {
                board.second[checkMap(pos).second.second]='_';
                board.second[checkMap(checkMap(pos).second.second).second.second]=board.second[pos];
                board.second[pos]='_';
                board.first+=2;
                return mBoards(board, checkMap(checkMap(pos).second.first).second.first, side, di, true);
            }
        }
        if(di==3)
        {
            if(cSpaceN(board, checkMap(pos).second.first) && !j)
            {
                board.second[checkMap(pos).second.first]=board.second[pos];
                board.second[pos]='_';
                board.first=1;
                return board;
            }else if(cJumpN(board, pos, checkMap(pos).second.first))
            {
                board.second[checkMap(pos).second.first]='_';
                board.second[checkMap(checkMap(pos).second.first).second.first]=board.second[pos];
                board.second[pos]='_';
                board.first+=2;
                return mBoards(board, checkMap(checkMap(pos).second.first).second.first, side, di, true);
            }
        }
    }
    return board;
}

std::vector<bo> getBoardsN(std::vector<bo> boards, int turn=0)
{
    bo temp;
    int lim=0;
    temp.first=-1;
    temp.second=boards[0].second;
    for(int i=0; i<boards[0].second.length(); ++i)
    {
        if((turn==0&&(boards[0].second[i]=='R'||boards[0].second[i]=='r'))||(turn==1&&(boards[0].second[i]=='B'||boards[0].second[i]=='b'))||boards[0].second[i]=='_')
            continue;
        for(int j=0; j<4; ++j)
        {
            
            temp=mBoards(boards[0], i, turn, j);
            if(temp.first>=lim)
            {
                if(temp.first>lim)
                {
                    boards.erase(boards.begin()+1,boards.end());
                    lim=temp.first;
                }
                boards.push_back(temp);
            }
        }
    }
    return boards;
}

