#include "tourney.h"

#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

void pick_kaiju(){
    vector<kaiju> monsters;
    int check;
    int pop_count;
    int gen_count = 0;
    cout << "1 for new random, 0 to load" << endl << "> ";
    std::cin >> check;
    if(check == 0){
        cout << "load how many?" << endl << "> ";
        cin >> pop_count;
        for(int i = 0; i < pop_count; ++i)
            monsters.push_back(kaiju(i));
        cout << "done loading." << endl
             << "loaded: " << monsters.size() << endl;
    }else if(check == 1){
        cout << "make how many?" << endl << "> ";
        cin >> pop_count;
        for(int i = 0; i < pop_count; ++i)
            monsters.push_back(kaiju('s'));
        cout << "done random generation." << endl
             << "made: " << monsters.size() << endl;
    }else{
        cout << "that wasn't a valid number." << endl;
        return;
    }
    
    doublelim(monsters);
}

void pick_nets(){
    vector<neuralNet> nets;
    string path = "currnet/";
    int pop_count;
    cout << "load how many?" << endl << "> ";
    cin >> pop_count;
    for(int i = 0; i < pop_count; ++i){
        path = "current/";
        if(i < 10){
            path += "net_00";
            path += std::to_string(i);
        }else if(i < 100 && i > 10){
            path += "net_0";
            path += std::to_string(i);
        }else{
            path += "net_";
            path += std::to_string(i);
        }
        nets.push_back(neuralNet(path));
    }

    doublelim(nets);

}

int main(){
    int check;
    cout << "1 for kaiju, 0 for nets" <<  endl << "> ";
    cin >> check;
    if(check == 1)
        pick_kaiju();
    else
        pick_nets();
    return 0;
}
