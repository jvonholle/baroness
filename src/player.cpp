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

bool win(string board, char turn){
    int count = 0;
    for(int i = 0; i < 32; ++i)
        if(board[i] == turn || board[i] == turn-34)
            count++;
    return (count == 0);    
}

int p_count(string board, char turn){
    cout << "p_cout called" << endl;
    int count = 0;
    for(int i = 0; i < 32; ++i)
        if(board[i] == turn || board[i] == turn-34)
            count++;
    return count;
}


int play(neuralNet & red, neuralNet & black, const int turns, const string startB){
    int t_count = 0;
    vector<string> game;
    game.push_back(startB);
    while(t_count < turns){
        game.push_back(red.go(game[t_count], true));
        if(win(game[t_count], 'r')){
            cout << "red wins!" << endl;
            return p_count(game[t_count], 'r') * 3;
        }
        cout << game[t_count] << endl;
        t_count++;
        game.push_back(black.go(game[t_count], false)); 
        if(win(game[t_count], 'b')){
            cout << "black wins" << endl;
            return p_count(game[t_count], 'b') * -5;
        }
        cout << game[t_count] << endl;
        t_count++;
    }
    return (p_count(game[t_count], 'r') - p_count(game[t_count], 'b'));
}
