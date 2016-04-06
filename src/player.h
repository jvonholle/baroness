#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "kaiju.h"

#include <utility>
using std::pair;
#include <string>
using std::string;

void play(neuralNet & red, neuralNet & black,int pc, const int & turns = 100, const string & startB ="rrrrrrrrrrrr________bbbbbbbbbbbb");

void play(kaiju & red, kaiju & black, int pc, const int & turns = 100, const string & startB = "rrrrrrrrrrrr________bbbbbbbbbbbb" );

#endif
