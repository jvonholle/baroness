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


#include "nnet.h"

//Garbage test function
//doesn't time
//quick and dirty to make sure everything compiles
int main()
{
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(1, 6);
	vector<vector<double>> test(3);
	for(int i = 0; i<3; ++i)
		for(int j = 0; j<i*10; ++j)
			test[i].push_back(uniform_dist(e1));
	string path;
	cout<< "Output test filename: ";
	cin >> path;
	writeNet(path, test);
	cout<< "done." << endl;
	cout<<"Input test filename: ";
	cin>> path;
	
	vector<vector<double>> test2=loadNet(path);
	cout << "levels: " << test2.size() << endl;
	for(size_t i = 0; i<test2.size(); ++i){
		cout << test2[i].size() << endl;
		for(size_t j = 0; j<test2[i].size(); ++j){
			cout << test2[i][j] << " ";
		}
		cout << endl;
	}
	vector<string> test_strings(32);
	vector<pair<double, string> > butt;
	butt = boardEval(test_strings, test2);
	for(size_t i =0; i<butt.size(); ++i)
		cout<<butt[i].first << endl;

	writeNet(path, test2);
	return 0;
}
