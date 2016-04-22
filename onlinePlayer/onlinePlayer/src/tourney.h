#ifndef TOURNEY_H_INCLUDED
#define TOURNEY_H_INCLUDED
#include "player.h"
#include <vector>
using std::vector;
#include <utility>
using std::pair;

pair<int, vector<neuralNet> > roundrobin(vector<neuralNet> & nets, const int & gen, const int & print_check = 0);

pair<int, vector<neuralNet> > single(vector<neuralNet> & nets, const int & gen, const int & print_check = 0);

vector<int> monsterfight(vector<kaiju> & monsters, const int & print_check = 0);

#endif
