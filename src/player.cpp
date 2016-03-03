#include "player.h"
#include <utility>
using std::pair;
using std::make_pair;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <algorithm>
using std::sort;

vector<ratedBoard> weighBoards(const neuralNet & player, const vector<bo> & boards){
    vector<ratedBoard> ratedBoards;
    for(size_t i = 0; i < boards.size(); ++i)
        ratedBoards.push_back(make_pair(boards[i], player.evaluate(boards[i].second)));
    return ratedBoards;
}

vector<bo> pickMove(const vector<ratedBoard> & boards, const int depth = 8){
    sort(boards.begin(), boards.end(),
            [=](size_t i1, size_t i2)
            {return boards[i1].second > boards[i2].second;});
    return({make_pair(1,boards[0].first)});
}

int play(const neuralNet & red, const nerualNet & black, const vector<string> startBoard ={"rrrrrrrrrrrr________bbbbbbbbbbbb"}, const int turns = 100){
    t_count = 0;
    vector<bo> boards = getBoardsN(startBoard, 0);
    vector<bo> game;
    vector<ratedBoard> redBoards;
    vector<ratedBoard> blackBoards;
    game.push_back(startBoard[0]);
    while(t_count < turns){
        redBoards = weighBoards(red, boards);

        blackBoards = weighBoards(black, boards);

        t_count++;
    }
    return 0;
}

int main(){
    neuralNet p1({1,1}, {1});
    neuralNet p2({1,1}, {1});

    return play(p1, p2);
}
