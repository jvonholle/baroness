//
//  movement.h
//  movtest
//
//  Created by BOB on 3/25/16.
//  Copyright (c) 2016 nick. All rights reserved.
//

#ifndef movtest_movement_h
#define movtest_movement_h

#include "movement.h"
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
    //creates the checkers move map
    MoveMap();
        
    moves getMoves(int pos);
    
    
    int getMove(int pos, int d);
   
    
private:
    std::map<int,pair<pair<int,int>,pair<int,int>>> board; 
};


//p1 is the piece thats jumping p2 is peice to be removed p3 is destination pos
void jumpEdit(std::string & board, int p1, int p2, int p3);

int whatTeam(char p);

void cKingN(std::string & board);

bool isKing(char p);

bool isEmpty(char s);

bool sameTeam(char p, int p2);

bool posJmp(std::string board,int pos, int turn, MoveMap & map);

bool jumpInternal(std::vector<std::string> & boards,std::string board, int pos, int turn, MoveMap & map, int initalDir, bool & clear);

//finds if theres jumps
bool jump(std::vector<std::string> & boards, int pos, int turn, MoveMap & map, int initalDir, bool & clear);

void moveEdit(std::string & board, int pos, int pos2);

void moveInternal(std::string & board, int pos, int dir, MoveMap & map);

void move(std::vector<std::string> & boards, int pos, int dir, int turn, MoveMap & map);

//generates moves
//turn
//  1=red
//  2=black
void makeBoards(std::vector<std::string> & boards, int turn, MoveMap & map);

std::vector<std::string> getBoardsN(std::vector<std::string> boards, bool turn);



#endif
