//
//  movement.cpp
//  checkers
//

#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <utility>
using std::make_pair;
using std::pair;


typedef  pair<pair<int,int>,pair<int,int>> moves;

class MoveMap{
public:
    MoveMap()
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
    
    moves getMoves(int pos)
    {
        if(pos<0 || pos>31)
            return board[-1];
        
        return board[pos];
    }
    
    int getMove(int pos, int d)
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
    
private:
    std::map<int,moves> board;
};



void cKingN(std::string & board){
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

bool sameTeam(char p, int p2)
{
    if(p=='b'||p=='B')
    {
        if(p2=='b'||p2=='B')
            return true;
        return false;
    }
    
    if(p=='r'||p=='R')
    {
        if(p2=='r'||p2=='R')
            return true;
        return false;
    }
    return false;
}

bool isEmpty(char s)
{
    if(s=='_')
        return true;
    return false;
}
// side/king
// cycle through moves when jumpd clear moves and only keep jumps

//finds if theres jumps
bool jump(std::vector<std::string> & boards, int pos, int turn, MoveMap & map)
{
    bool jump = false;
    std::string board;
    board = boards[0];
    int dir;
    while(true)
    {
        if(turn==1||isKing(board[pos]))
        {
            dir = 0;
            if(!sameTeam(board[pos], board[map.getMove(pos,dir)])&&!isEmpty(map.getMove(pos,dir)))
            {
                if(isEmpty(board[map.getMove(map.getMove(pos,dir) ,dir) ] ) )
                {
                    board[map.getMove(map.getMove(pos,dir) ,dir)]=board[pos];
                    board[pos]='_';
                    board[map.getMove(pos,dir)]='_';
                    jump = true;
                    pos = map.getMove(map.getMove(pos,dir) ,dir);
                    
                }
                
            }
        }
        else if(turn==1||isKing(board[pos]))
        {
            dir=1;
            if(!sameTeam(board[pos], board[map.getMove(pos,dir)])&&!isEmpty(map.getMove(pos,dir)))
            {
                if(isEmpty(board[map.getMove(map.getMove(pos,dir) ,dir) ] ) )
                {
                    board[map.getMove(map.getMove(pos,dir) ,dir)]=board[pos];
                    board[pos]='_';
                    board[map.getMove(pos,dir)]='_';
                    jump = true;
                    pos = map.getMove(map.getMove(pos,dir) ,dir);
                    
                }
                
            }
        }
        else if(turn==2||isKing(board[pos]))
        {
            dir = 0;
            if(!sameTeam(board[pos], board[map.getMove(pos,dir)])&&!isEmpty(map.getMove(pos,dir)))
            {
                if(isEmpty(board[map.getMove(map.getMove(pos,dir) ,dir) ] ) )
                {
                    board[map.getMove(map.getMove(pos,dir) ,dir)]=board[pos];
                    board[pos]='_';
                    board[map.getMove(pos,dir)]='_';
                    jump = true;
                    pos = map.getMove(map.getMove(pos,dir) ,dir);
                    
                }
                
            }
        }
        else if(turn==2||isKing(board[pos]))
        {
            dir=1;
            if(!sameTeam(board[pos], board[map.getMove(pos,dir)])&&!isEmpty(map.getMove(pos,dir)))
            {
                if(isEmpty(board[map.getMove(map.getMove(pos,dir) ,dir) ] ) )
                {
                    board[map.getMove(map.getMove(pos,dir) ,dir)]=board[pos];
                    board[pos]='_';
                    board[map.getMove(pos,dir)]='_';
                    jump = true;
                    pos = map.getMove(map.getMove(pos,dir) ,dir);
                    
                }
                
            }
        }


    }
    return jump;
}

//generates moves
std::vector<std::string> makeBoards(std::vector<std::string> & boards, int turn, MoveMap & map)
{
    bool jumped=false;
    std::string board;
    board = boards[0];
    for(int pos=0; pos>boards[0].size(); ++pos)
    {
        for(int dir=0; dir<4; ++dir)
        {
            //jumped = jump(boards,);

            if(!jumped)
            {
                
            }
        }
    }
    return boards;
}

std::vector<std::string> getBoardsN(std::vector<std::string> boards,int pos, int turn, int di)
{
    MoveMap moveCheck;
    std::pair<int, std::string> temp;
    temp.first= -1;
    int lim=0;
    temp.second =boards[0];
    for(int i=0; i<boards[0].length(); ++i)
    {
        if((turn==0&&sameTeam(boards[0][i],'R'))||(turn==1&&sameTeam(boards[0][i],'B'))||isEmpty(boards[0][i]))
            continue;
        for(int j=0; j<4; ++j)
        {
            
            if(turn == 1 && boards[0][i] == 'R'){
                //temp = makeBoards(boards, 1, moveCheck);
            }else if(turn==0 && boards[0][i] == 'B'){
                //temp = makeBoards(boards[0], i, 3, j, temp.first);
            }else{
                //temp = mmakeBoards(boards[0], i, turn, j, temp.first);
            }
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
    for(int i = 0; i< boards.size(); ++i)
        cKingN(boards[i]);
    return boards;
}


/*
 bool cSpaceN(std::string & board, int pos)
 {
 if(board[pos]!='_')
 return false;
 return true;
 }
 
 bool cJumpN(std::string & board, int mPos, int ePos)
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
 */
