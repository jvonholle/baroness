//
//  alphbeta.h
//  checkersJ
//
//  Created by BOB on 3/5/16.
//  Copyright (c) 2016 nick. All rights reserved.
//
#ifndef __checkersJ__alphbeta__
#define __checkersJ__alphbeta__
#include <iostream>
#include <vector>
#include <string>
#include "movement.h"
#include "nnet.h"
double max(double a, double b)
{
    if(a>b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

double min(double a, double b)
{
    if(a<=b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

std::vector<double> toDubb(std::string str, bool side, double king);

struct node{
    
    std::string move;
    double w;
    std::vector<node*> children;
    
    node(){
        //default shit
    };
    
    node(node & start)
    {
        //copy constructor
    };
    
    node(std::string str)
    {
        move = str;
        w=0;
    };
    
    ~node()
    {
        for(int i=0; i<children.size(); ++i)
        {
            delete children[i];
        }
    }
    
    void birth(std::string str)
    {
        node * temp;
        temp = new node(str);
        children.push_back(temp);
    }
    
    void populate()
    {
        std::vector<std::string> moves;
        //getBoardsN(move,1);
        if(moves.size()>0)
        {
            for(int i=0; i<moves.size();++i)
            {
                birth(moves[i]);
            }
        }
    }
    
    std::string bestMove()
    {
        std::string best= "";
        int top = 0;
        if(children.size()<=0)
        {
            std::cout<<"Error: best move in node" <<std::endl;
            return "bad";
        }
        else{
            std::cout <<"enter best move" <<std::endl;
            top=children[0]->w;
            std::cout << "top" <<top <<std::endl;
        }
        for(int i=1; i<children.size(); ++i)
        {
            if(top<children[i]->w)
            {
                best=children[i]->move;
                top =children[i]->w;
            }
        }
        return best;
    }
};

double ab(node* root,int depth, double a, double b, bool maximize, bool side, neuralNet& nn);

void build(node* root, int depth, neuralNet& nn1, int move=1)
{
    std::vector<std::string> moves;
    moves.push_back(root->move);
    
    moves = getBoardsN(moves, move%2==1);
    double w=0;
    for(int j=0; j<moves.size(); ++j)
    {
        w = nn1.evaluate(toDubb(moves[j], true, 1.5));
        std::cout <<w <<moves[j] <<std::endl;
        root->birth(moves[j]);
        root->children[j]->w=w;
    }
    if(depth>0)
    {
        for(int i=0; i<root->children.size(); ++i)
        {
            build(root->children[i], depth-1, nn1,move+1);
        }
    }
}

std::string absearch(node* root, int depth, bool side, neuralNet& nn) //add nuralnetwork
{
    build(root, depth, nn, side);
    ab(root, depth, -100000, 100000, true, true, nn);
    for(int i=0; i<root->children.size();++i)
    {
        std::cout<< root->children[i]->w <<std::endl;
    }
    return root->bestMove();
}

double ab(node* root,int depth, double a, double b, bool maximize, bool side, neuralNet& nn)
{
    int v; // tracking variable for weight
    if(depth<=0)
    {
        return root->w;
        //return what it should
    }else if(maximize)
    {
        v=-10000;
        for(int i=0; i<root->children.size(); ++i)
        {
            std::cout<< "LOOOOOOOP"<<root->children[i]->move <<std::endl;
            v=max(v, ab(root->children[i], depth-1, a, b, false, side, nn));
            a=max(a,v);
            if(b<=a)
            {
                break;
            }

        }
        return v;
    }
    else
    {
        v=10000;
        for(int i=0; i<root->children.size();++i)
        {
            std::cout<< "LOOP"<<root->children[i]->move  <<std::endl;
            v=min(v, ab(root->children[i], depth-1, a, b, true, side, nn));
            b=min(b, v);
            if(b<=a)
            {
                
                break;
            }
        }
        return v;
    }
    return v;
}


//side
//  true=red
//  false=black
std::vector<double> toDubb(std::string str, bool side, double king)
{
    std::vector<double> dubbs;
    for(int i=0; i<str.size(); ++i)
    {
        switch(str[i])
        {
            case 'r':
                dubbs.push_back(1);
                break;
                
            case 'R':
                dubbs.push_back(king);
                break;
                
            case 'b':
                dubbs.push_back(-1);
                break;
                
            case 'B':
                dubbs.push_back(-king);
                break;
                
            case '_':
                dubbs.push_back(0);
                break;
            default:
                std::cout <<"eRRoR" <<std::endl;
        }
    }
    if(!side)
    {
        for(int i=0; i<dubbs.size(); ++i)
        {
            dubbs[i]*=-1;
        }
    }
    return dubbs;
}
#endif /* defined(__checkersJ__alphbeta__) */
