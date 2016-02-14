//function descriptions in source file (nnet.cpp)
#ifndef NNET_H_INCLUDED
#define NNET_H_INCLUDED

#include <vector>
using std::vector;
#include <fstream>
using std::ifstream;
using std::ofstream;
#include <string>
using std::string;
#include <chrono>
using std::chrono::system_clock;
#include <utility>
using std::pair;
#include <cstddef>
using std::size_t;
#include <queue>
using std::priority_queue;

bool writeNet(const string & path,const vector<vector<double> > & nNet);

vector<vector<double> > loadNet(const string & path);

double phi(double x);

double activate(const vector<double> & sum);

void boardPos(vector<double> & numBoard, const string & board);

//priority_queue<double, string> boardEval(const vector<string> boards, const vector<vector<double> > & nNet);

vector<pair<double, string> > boardEval(vector<string> & boards ,vector<vector<double> > & nNet);

#endif
