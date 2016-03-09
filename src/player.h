#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "nnet.h"

#include <utility>
using std::pair;
#include <string>
using std::string;

int play(neuralNet & red, neuralNet & black, const int turns = 100, const string startB ="rrrrrrrrrrrr________bbbbbbbbbbbb");

#endif
