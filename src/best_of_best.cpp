#include "player.h"
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;
int main(){
    kaiju zero(666);
    kaiju one(731);
    kaiju two(999);
    
    neuralNet best0("best");
    neuralNet best1("best1");
    
    play(zero, one, 0);
    play(zero, two, 0);
    play(zero, best0, 0);
    play(zero, best1, 0);
    
    play(one, zero, 0);
    play(one, two, 0);
    play(one, best0, 0);
    play(one, best1, 0);
    
    play(two, zero, 0);
    play(two, one, 0);
    play(two, best0, 0);
    play(two, best1, 0);
    
    play(best0, zero, 0);
    play(best0, one, 0);
    play(best0, two, 0);
    play(best0, best1, 0);
    
    play(best1, zero, 0);
    play(best1, one, 0);
    play(best1, two, 0);
    play(best1, best0, 0);
    
    vector<int> scores;
    
    scores.push_back(zero.get_score());
    scores.push_back(one.get_score());
    scores.push_back(two.get_score());
    scores.push_back(best0.get_score());
    scores.push_back(best1.get_score());
    
    int check = -100;
    int winner;
    for(int i = 0; i < 5; ++i){
        if(scores[i] > check){
            check = scores[i];
            winner = i;
        }
    }
    cout << "winner is: " << winner << endl;
    cout << "0: 666 || 1: 731 || 2: 999 || 3: best || 4: best1" << endl;
    return 0;
}