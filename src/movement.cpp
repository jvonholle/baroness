//
//  movement.cpp
//  movtest
//
//  Created by BOB on 3/28/16.
//  Copyright (c) 2016 nick. All rights reserved.
//

#include "movement.h"

//Move map class
//used to chart possible moves on a checkers board
MoveMap::MoveMap()
{
    board[0]= make_pair(make_pair(4,5),make_pair(-1,-1));
    board[1]= make_pair(make_pair(5,6),make_pair(-1,-1));
    board[2]= make_pair(make_pair(6,7),make_pair(-1,-1));
    board[3]= make_pair(make_pair(7,-1),make_pair(-1,-1));
    board[4]= make_pair(make_pair(-1,8),make_pair(-1,0));
    board[5]= make_pair(make_pair(8,9),make_pair(0,1));
    board[6]= make_pair(make_pair(9,10),make_pair(1,2));
    board[7]= make_pair(make_pair(10,11),make_pair(2,3));
    board[8]= make_pair(make_pair(12,13),make_pair(4,5));
    board[9]= make_pair(make_pair(13,14),make_pair(5,6));
    board[10]= make_pair(make_pair(14,15),make_pair(6,7));
    board[11]= make_pair(make_pair(15,-1),make_pair(7,-1));
    board[12]= make_pair(make_pair(-1,16),make_pair(-1,8));
    board[13]= make_pair(make_pair(16,17),make_pair(8,9));
    board[14]= make_pair(make_pair(17,18),make_pair(9,10));
    board[15]= make_pair(make_pair(18,19),make_pair(10,11));
    board[16]= make_pair(make_pair(20,21),make_pair(12,13));
    board[17]= make_pair(make_pair(21,22),make_pair(13,14));
    board[18]= make_pair(make_pair(22,23),make_pair(14,15));
    board[19]= make_pair(make_pair(23,-1),make_pair(15,-1));
    board[20]= make_pair(make_pair(-1,24),make_pair(-1,16));
    board[21]= make_pair(make_pair(24,25),make_pair(16,17));
    board[22]= make_pair(make_pair(25,26),make_pair(17,18));
    board[23]= make_pair(make_pair(26,27),make_pair(18,19));
    board[24]= make_pair(make_pair(28,29),make_pair(20,21));
    board[25]= make_pair(make_pair(29,30),make_pair(21,22));
    board[26]= make_pair(make_pair(30,31),make_pair(22,23));
    board[27]= make_pair(make_pair(31,-1),make_pair(23,-1));
    board[28]= make_pair(make_pair(-1,-1),make_pair(-1,24));
    board[29]= make_pair(make_pair(-1,-1),make_pair(24,25));
    board[30]= make_pair(make_pair(-1,-1),make_pair(25,26));
    board[31]= make_pair(make_pair(-1,-1),make_pair(26,27));
    board[-1]= make_pair(make_pair(-1,-1),make_pair(-1,-1));
}

moves MoveMap::getMoves(int pos)
{
    if(pos<0 || pos>31)
        return board[-1];
    
    return board[pos];
}

int MoveMap::getMove(int pos, int d)
{
    if(pos<0 || pos>31)
        return board[-1].first.first;
    
    switch(d)
    {
        case 0:
            return board[pos].first.first;
            
        case 1:
            return board[pos].first.second;
            
        case 2:
            return board[pos].second.first;
            
        case 3:
            return board[pos].second.second;
            
        default:
            return -1;
    }
    
}


//Move Gen hleper functions
void jumpEdit(std::string & board, int p1, int p2, int p3)
{
    board[p3]=board[p1];
    board[p2]='_';
    board[p1]='_';
}

int whatTeam(char p)
{
    if(p=='r'||p=='R')
        return 1;
    if(p=='b'||p=='B')
        return 0;
    return -1;
}

void cKingN(std::string & board)
{
    for(int i = 0; i < 32; ++i){
        if(i >= 0 && i < 4 ){
            if(board[i] == 'b')
                board[i] = 'B';
        }else if(i>= 28 && i < 32){
            if(board[i] == 'r')
                board[i] = 'R';
        }
    }
}

bool isKing(char p)
{
    if(p=='R'||p=='B')
        return true;
    return false;
}


bool isEmpty(char s)
{
    if(s=='_')
        return true;
    return false;
}

bool sameTeam(char p, int p2)
{
    if(isEmpty(p2))
        return true;
    if(whatTeam(p)==whatTeam(p2))
        return true;
    return false;
}

bool posJmp(std::string board,int pos, int turn, MoveMap & map)
{
    for(int dir=0; dir<4; ++dir)
    {
        if((turn==1||isKing(board[pos]))&&(dir==0||dir==1))
        {
            
            if(!sameTeam(board[pos], board[map.getMove(pos,dir)])&&isEmpty(board[map.getMove(map.getMove(pos,dir),dir)]))
            {return true;}
        }
        else if((turn==0||isKing(board[pos]))&&(dir==2||dir==3))
        {
            if(!sameTeam(board[pos], board[map.getMove(pos,dir)])&&!isEmpty(map.getMove(pos,dir))&&isEmpty(board[map.getMove(map.getMove(pos,dir),dir)]))
            {
                return true;
            }
        }
        
    }
    return false;
}

bool jumpInternal(std::vector<std::string> & boards,std::string board, int pos, int turn, MoveMap & map, int initalDir, bool & clear)
{
    bool jump = false;
    int dir = 0;
    //std::cout << initalDir<<std::endl;
    if(initalDir>=0&&initalDir<4)
    {
        if((turn==1||isKing(board[pos]))&&(initalDir==0||initalDir==1))
        {
            
            if(!sameTeam(board[pos], board[map.getMove(pos,initalDir)])&&isEmpty(board[map.getMove(map.getMove(pos,initalDir),initalDir)]))
            {
                jumpEdit(board, pos, map.getMove(pos,initalDir), map.getMove(map.getMove(pos,initalDir),initalDir));
                jump = true;
                pos = map.getMove(map.getMove(pos,initalDir) ,initalDir);
                for(dir=0; dir<4; ++dir)
                {
                    jumpInternal(boards, board, pos, turn, map, dir, clear);
                }
                //std::cout<<board<<"go up" <<std::endl;
            }
        }
        else if((turn==0||isKing(board[pos]))&&(initalDir==2||initalDir==3))
        {
            if(!sameTeam(board[pos], board[map.getMove(pos,initalDir)])&&!isEmpty(map.getMove(pos,initalDir))&&isEmpty(board[map.getMove(map.getMove(pos,initalDir),initalDir)]))
            {
                jumpEdit(board, pos, map.getMove(pos,initalDir), map.getMove(map.getMove(pos,initalDir),initalDir));
                jump = true;
                pos = map.getMove(map.getMove(pos,initalDir) ,initalDir);
                for(dir=0; dir<4; ++dir)
                {
                    jumpInternal(boards, board, pos, turn, map, dir, clear);
                }
                //std::cout<<board<<"go up"<<std::endl;
            }
        }
        
        {
            if(!jump)
            {
                if(!(boards[boards.size()-1]==board))
                {
                    if(clear)
                    {
                        clear=false;
                        if(boards.size()>1)
                        {
                            std::string tmp = boards[0];
                            boards.clear();
                            boards.push_back(tmp);
                        }
                    }
                    if(!posJmp(board, pos, turn, map))
                        boards.push_back(board);
                }
            }
            return jump;
        }
        
    }
    
    return jump;
}

//finds if theres jumps
bool jump(std::vector<std::string> & boards, int pos, int turn, MoveMap & map, int initalDir, bool & clear)
{
    bool jump = false;
    std::string board;
    board = boards[0];
    int dir=0;
    if(initalDir>=0&&initalDir<4)
    {
        if((turn==1||isKing(board[pos]))&&(initalDir==0||initalDir==1))
        {
            
            if(!sameTeam(board[pos], board[map.getMove(pos,initalDir)])&&isEmpty(board[map.getMove(map.getMove(pos,initalDir),initalDir)]))
            {
                jumpEdit(board, pos, map.getMove(pos,initalDir), map.getMove(map.getMove(pos,initalDir),initalDir));
                jump = true;
                pos = map.getMove(map.getMove(pos,initalDir) ,initalDir);
                for(dir=0; dir<4; ++dir)
                {
                    jumpInternal(boards, board, pos, turn, map, dir, clear);
                }
            }
        }
        else if((turn==0||isKing(board[pos]))&&(initalDir==2||initalDir==3))
        {
            if(!sameTeam(board[pos], board[map.getMove(pos,initalDir)])&&!isEmpty(map.getMove(pos,initalDir))&&isEmpty(board[map.getMove(map.getMove(pos,initalDir),initalDir)]))
            {
                jumpEdit(board, pos, map.getMove(pos,initalDir), map.getMove(map.getMove(pos,initalDir),initalDir));
                jump = true;
                pos = map.getMove(map.getMove(pos,initalDir) ,initalDir);
                for(dir=0; dir<4; ++dir)
                {
                    jumpInternal(boards, board, pos, turn, map, dir, clear);
                }
            }
        }
        else
        {
            return jump;
        }
        
    }
    return jump;
}

void moveEdit(std::string & board, int pos, int pos2)
{
    board[pos2]=board[pos];
    board[pos]='_';
}

void moveInternal(std::string & board, int pos, int dir, MoveMap & map)
{
    int p2 = map.getMove(pos, dir);
    if(isEmpty(board[p2]))
    {
        moveEdit(board, pos, p2);
    }
}

void move(std::vector<std::string> & boards, int pos, int dir, int turn, MoveMap & map)
{
    std::string board = boards[0];
    if(turn==1||isKing(board[pos]))
    {
        if(dir==0||dir==1)
        {
            moveInternal(board, pos, dir, map);
        }
    }
    if(turn==0||isKing(board[pos]))
    {
        if(dir==2||dir==3)
        {
            moveInternal(board, pos, dir, map);
        }
    }
    if(board!=boards[0])
    {
        boards.push_back(board);
    }
}

//generates moves
//turn
//  1=red
//  2=black
void makeBoards(std::vector<std::string> & boards, int turn, MoveMap & map)
{
    bool jumped=false;
    bool clear=true;
    std::string board;
    board = boards[0];
    for(int pos=0; pos<board.size(); ++pos)
    {
        if(!isEmpty(board[pos]))
        {
            if(turn!=whatTeam(board[pos]))
                continue;
            {
                for(int dir=0; dir<4; ++dir)
                {
                    if(!jumped)
                    {
                        jumped=jump(boards, pos, turn, map, dir,clear);
                    }
                    else
                    {
                        jump(boards, pos, turn, map, dir,clear);
                    }
                    
                    //std::cout<<jumped <<std::endl;
                    if(!jumped)
                        move(boards, pos, dir, turn, map);
                }
            }
        }
    }
    //return boards;
}

std::vector<std::string> getBoardsN(std::vector<std::string> boards, bool turn)
{
    MoveMap moveCheck;
    
    makeBoards(boards, turn, moveCheck);
    
    for(int i = 0; i< boards.size(); ++i)
        cKingN(boards[i]);
    boards.erase(boards.begin());
    return boards;
}
