#include "../src/kaiju.h"
//#include <random>
//using std::random_device;
//using std::mt19937;
#include <algorithm>
#include <iostream>
using std::cout;
using std::endl;


int main(){
    
    vector<double> startW;
    vector<string> game;
    
//    random_device rd;
//    mt19937 randomG(rd());
    int t_count = 0;
//    auto d = std::uniform_real_distribution<> (-1,1);
    bool valid;
    double redscore =0;
    double blackscore =0;
//    for(int i = 0; i < 10; ++i){
//        for(int j = 0; j < 3700; ++j)
//            startW.push_back(d(randomG));
    
//        neuralNet red({32, 40, 40, 20, 1}, startW);
        startW.clear();

        kaiju red('l');
            
        kaiju black('j');
        t_count =0;
        game.clear();
        game.push_back("rrrrrrrrrrrr________bbbbbbbbbbbb");
        while(t_count < 200){
            auto temp_nl = red.go(game[t_count], true);
    
            if(temp_nl.second){
                valid = false;
                auto tempstrings = getBoardsN({game[t_count]}, true);
                for(int i = 0; i < tempstrings.size(); ++i)
                    if(temp_nl.first == tempstrings[i])
                        valid = true;
                if(valid){
                    game.push_back(temp_nl.first);
                    t_count++;
                }else{
                    cout << "not a valid move from red!" << endl;
                    cout << temp_nl.first << endl;
                    blackscore++;
                    break;
                }
            }else{
                cout << "done, black wins." << endl;
                blackscore++;
                break;
            }
            temp_nl = black.go(game[t_count], false);
    
            if(temp_nl.second){
                valid = false;
                auto tempstrings = getBoardsN({game[t_count]}, false);
                for(int i = 0; i < tempstrings.size(); ++i)
                    if(temp_nl.first == tempstrings[i])
                        valid = true;
                if(valid){
                    game.push_back(temp_nl.first);
                    t_count++;
                }else{
                    cout << "not a valid move from black!" << endl;
                    cout << temp_nl.first << endl;
                    redscore++;
                    break;
                }
            }else{
                cout << "done, red wins." << endl;
                redscore++;
                break;
            }
        }  
    //}
    
    cout << "black won: " << blackscore << " red won: " << redscore << ", which is " << blackscore/(redscore+blackscore) << "\%" << endl;
    return 0;
}
