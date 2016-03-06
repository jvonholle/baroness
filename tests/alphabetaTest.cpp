//
//  alphabetaTest.cpp
//  checkersJ
//
//  Created by BOB on 3/5/16.
//  Copyright (c) 2016 nick. All rights reserved.
//

#include <iostream>
#include <string>
#include "alphbeta.h"
#include "nnet.h"

int main()
{
    std::string path = "/Users/nicolaussegler/Desktop/Gitrepos/baroness/outt";
    neuralNet net1(path);
    
    std::string oBoard = "rrrrrrrrrrr_______rbbbb_bbbbbbbb";
    
    node* root;
    root = new node(oBoard);
    
    std::string move;
    move = absearch(root, 2, false, net1);
    
    std::cout <<oBoard <<std::endl <<move <<std::endl;
    
    
    
    return 0;
}
