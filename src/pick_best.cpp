#include "tourney.h"

#include <iostream>
using std::cout;
using std::endl;


int main(){
    vector<kaiju> monsters;
    int check;
    int pop_count;
    int gen_count = 0;
    cout << "1 for new random, 0 to load" << endl << "> ";
    std::cin >> check;
    if(check == 0){
        cout << "load how many?" << endl << "> ";
        std::cin >> pop_count;
        for(int i = 0; i < pop_count; ++i)
            monsters.push_back(kaiju(i));
        cout << "done loading." << endl
             << "loaded: " << monsters.size() << endl;
    }else if(check == 1){
        cout << "make how many?" << endl << "> ";
        std::cin >> pop_count;
        for(int i = 0; i < pop_count; ++i)
            monsters.push_back(kaiju('s'));
        cout << "done random generation." << endl
             << "made: " << monsters.size() << endl;
    }else{
        cout << "that wasn't a valid number." << endl;
        return 0;
    }
    
    doublelim(monsters);
    
    return 0;
}