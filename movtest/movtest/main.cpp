//
//  main.cpp
//  movtest
//
//  Created by BOB on 3/25/16.
//  Copyright (c) 2016 nick. All rights reserved.
//

#include <iostream>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <utility>
using std::pair;
using std::make_pair;
#include "movement.h"

int main()
{
    for(int ii=0; ii<10000; ++ii)
    {
    std::string board = "__r____rr__b____bb______r_br__b_";
    vector<string> boards;
    //r____b__________________________  single
    //r____b________b_________________  double line
    //r____b_______b__________________  double L
    //R____bbb_____b_b_____bb_________  round the board king jump
    //R___b___________________________  edge jump
    //black jumps
    //__________r______r________r____b  L jump
    //std::cout << "enter a board to get moves for :";
    
    //std::cin >> board;
    
    //std::cout <<"getting boards for :" <<board <<"\n" <<std::endl;
    
    boards.push_back(board);
    //jumped = jump(boards, 31, 2, map);
    
//    std::cout << jumped <<" " <<boards[0] <<std::endl;
//    if(jumped)
//    {
//        std::cout <<boards[1]<<" printed " <<std::endl;
//    }
    
    boards = getBoardsN(boards, false);
    int i=1;
    for( auto x : boards)
    {
        std::cout << x <<std::endl;
        ++i;
    }
    }
    
    return 0;
}
