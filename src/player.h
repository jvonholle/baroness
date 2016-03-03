#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "movement.h"
#include "nnet.h"
#include <utility>
using std::pair;
#include <string>
using std::string;
#include <vector>
using std::vector;

typedef pair<bo, double> ratedBoard;

vector<ratedBoard> weighBoards(const neuralNet & player, const vector<bo> & boards);

vector<bo> pickMove(const vector<ratedBoard> & boards, const int depth = 8);

int play(const neuralNet & red, const neuralNet & black, const vector<string> & startBoard = {"rrrrrrrrrrrr________bbbbbbbbbbbb"}, const int turns = 100);

#endif
