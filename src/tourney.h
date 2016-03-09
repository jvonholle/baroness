#ifndef TOURNEY_H_INCLUDED
#define TOURNEY_H_INCLUDED
#include "player.h"
#include <vector>
using std::vector;
#include <utility>
using std::pair;

pair<int, vector<neuralNet> > roundrobin(vector<neuralNet> & nets);

#endif
