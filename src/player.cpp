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


int p_count(string board, char turn){
    int count = 0;
    for(int i = 0; i < 32; ++i)
        if(board[i] == turn || board[i] == turn-32)
            count++;
    return count;
}


int play(neuralNet & red, neuralNet & black,int pc, const int turns, const string startB){
    int t_count = 0;
    vector<string> game;
    game.clear(); 
    game.push_back(startB);
    while(t_count < turns){
        auto temp = red.go(game[t_count], true);
        if(temp.second){
            game.push_back(temp.first);
            t_count++;
            //cout << "red move:" << endl;
            if(pc == 1)
                cout << game[t_count] << endl;
        }else{
            cout << "black wins" << endl;
            return (p_count(game[t_count], 'b') * -5);
        }
        temp = black.go(game[t_count], false);
        if(temp.second){
            game.push_back(temp.first);
            t_count++;
            //cout << "black move:" << endl;
            if(pc == 1)
                cout << game[t_count] << endl;
        }else{
            cout << "red wins" << endl;
            return (p_count(game[t_count], 'r') * 3);
        }
    }
    cout << "draw!" << endl;
    return (p_count(game[t_count], 'r') - p_count(game[t_count], 'b'));
}
