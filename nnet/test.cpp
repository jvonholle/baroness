#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <cstddef>
using std::size_t;
#include <random>
#include <queue>
using std::priority_queue;
#include <algorithm>
using std::sort;
#include <chrono>
using std::chrono::steady_clock;
#include <random>
#include <map>
using std::map;

#include "nnet.h"
//Function boardTestGen
//takes an int for size, returns a vector of strings
//strings are random either r R _ b B
//not realistic piece counts
vector<string> boardTestGen(const int & num)
{
	vector<string> rVec;
	string board;
	//possible pieces
	map<int, char> boardPick;
	boardPick[0]='_';
	boardPick[1]='r';
	boardPick[2]='R';
	boardPick[3]='b';
	boardPick[4]='B';

	//random number between 0 and 4
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0,4);

	for(int i = 0; i<num; ++i){
		board = "";
		for(int j = 0; j<32; ++j)
			board+=(boardPick[dis(gen)]);
	rVec.push_back(board);
	}
	return rVec;
}
//Test Function
//Times calls to user input number of tests of boardEval
//Further test capability to be decided.
int main()
{
	//Declare Variables
	size_t count;
	vector<vector<double> > test;
	string path;
	vector<string> boardTest;
	vector<string> startBtest = {"rrrrrrrrrrrr________bbbbbbbbbbbb"};
	vector<pair<double, string> > rTest;
	//Fill test vectors
	//Prompt user for input
//	cout << "Number of times to run boardEval: ";
//	cin >> count;
	cout << "Path to input file. Blondie24 sized net is included in file blondie in this directory." << endl << ">";
	cin >> path;
	test = loadNet(path);
	//Run and time loop boardTest = boardTestGen(100);
	auto b = steady_clock::now();		
	rTest = boardEval(boardTest, test);
	auto e = steady_clock::now();
	auto diff = e - b;
	cout << "Time 100: " << std::chrono::duration<double> (diff).count() << endl;
	boardTest = boardTestGen(1000);
	b = steady_clock::now();		
	rTest = boardEval(boardTest, test);
	e = steady_clock::now();
	diff = e - b;
	cout << "Time 1,000: " << std::chrono::duration<double> (diff).count() << endl;
	boardTest = boardTestGen(10000);
	b = steady_clock::now();		
	rTest = boardEval(boardTest, test);
	e = steady_clock::now();
	diff = e - b;
	cout << "Time 10,000: " << std::chrono::duration<double> (diff).count() << endl;
	boardTest = boardTestGen(100000);
	b = steady_clock::now();		
	rTest = boardEval(boardTest, test);
	e = steady_clock::now();
	diff = e - b;
	cout << "Time 100,000: " << std::chrono::duration<double> (diff).count() << endl;
//	boardTest = boardTestGen(1000000);
//	b = steady_clock::now();		
//	rTest = boardEval(boardTest, test);
//	e = steady_clock::now();
//	diff = e - b;
//	cout << "Time 1,000,000 boards: " << std::chrono::duration<double> (diff).count() << endl;
	for(int i =0; i<rTest.size(); ++i){
		if(i%5000==0){
			cout << "i: "<< i<< " " << rTest[i].first << " " <<  rTest[i].second << endl;
		}
}

	
	rTest = boardEval(startBtest, test);
	writeNet("out", test);
	for(int i =0; i<rTest.size(); ++i)
		cout << "i: "<< i<< " " << rTest[i].first << " " <<  rTest[i].second << endl;
	return 0;
}

