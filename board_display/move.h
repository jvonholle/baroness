//
//  move.h
//  first
//
//  Created by BOB on 1/20/16.
//  Copyright (c) 2016 Heartbreak Gorillas. All rights reserved.
//

#ifndef first_move_h
#define first_move_h

#include <vector>
#include <iostream>

bool jumpCheck(const std::vector<char> &board, int pos);

bool move(const std::vector<char> & board, int pos);

std::vector<char> moves(std::vector<char> & board,int peice, char side)
{
    
    if(side=='b'||side=='B')
    {
        
    }
    else if(side=='r'||side=='R')
    {
        
        for(int ii=32; ii>=0; --ii)
        {
            std::cout << board[ii] <<std::endl;
            if(board[ii]=='r')
               {
                   if(((ii+4)/4)==((ii+5)/4))
                   {
                       if(board[ii+5]=='b')
                       {
                           board[ii+9] = 'r';
                           board[ii+5] = '_';
                       }else{
                           board[ii+5] = 'r';
                       }
                       
                       if(board[ii+4]=='b')
                       {
                           board[ii+4] = '_';
                           board[ii+8] = 'r';
                       }else{
                           board[ii+4] = 'r';
                       }
                   }else{
                       board[ii+4] = 'r';
                   }
                   
               }
        }
    }
    return board;
}

bool move(const std::vector<char> & board , int pos)
{
    int m1, m2;
    m1 = pos+4;
    m2 = pos+5;
    
    if(board[m1]=='b')
    {
        if(jumpCheck(board, m1))
        {
            
        }
    }
    
}

bool jumpCheck(const std::vector<char> & board, int pos)
{
}

#endif
