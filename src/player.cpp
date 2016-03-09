#include "player.h"

#include <utility>
using std::pair;
using std::make_pair;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;

void printB(string board){
    for(int i = 1; i < 9; ++i){
        cout << "|";
        for(int j = 1; j < 5; ++j){
            cout << "_|"<<board[(i*j)-1] << "|";
        }
        cout << endl;
    }
}

int p_count(string board, char turn){
    int count = 0;
    for(int i = 0; i < 32; ++i)
        if(board[i] == turn || board[i] == turn-32)
            count++;
    return count;
}


int play(neuralNet & red, neuralNet & black, const int turns, const string startB){
    int t_count = 0;
    vector<string> game;
    game.push_back(startB);
    
    while(t_count < turns){
        auto temp = red.go(game[t_count], true);
        if(temp.second){
            game.push_back(temp.first);
            t_count++;
            cout << "red move:" << endl;
            printB(game[t_count]);
        }else{
            cout << "black wins" << endl;
            return (p_count(game[t_count], 'b') * -5);
        }
        temp = black.go(game[t_count], false);
        if(temp.second){
            game.push_back(temp.first);
            t_count++;
            cout << "black move:" << endl;
            printB(game[t_count]);
        }else{
            cout << "red wins" << endl;
            return (p_count(game[t_count], 'r') * 3);
        }
    }
    cout << "draw!" << endl;
    return (p_count(game[t_count], 'r') - p_count(game[t_count], 'b'));
}
