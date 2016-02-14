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
	
	vector<vector<double > > test(4);
	for(int i=0; i< 32; ++i)
		test[0].push_back(i);
	for(int i=0; i< 40; ++i)
		test[1].push_back(i);
	for(int i=0; i< 10; ++i)
		test[2].push_back(i);
	test[3].push_back(1);
	string path;
	cout<< "Output test filename: ";
	cin >> path;
	writeNet(path, test);
	cout<< "done." << endl;
	cout<<"Input test filename: ";
	cin>> path;
	
	vector<vector<double> > test2=loadNet(path);
	cout << "levels: " << test2.size() << endl;
	for(size_t i = 0; i<test2.size(); ++i){
		cout << test2[i].size() << endl;
		for(size_t j = 0; j<test2[i].size(); ++j){
			cout << test2[i][j] << " ";
		}
		cout << endl;
	}
	vector<string> test_strings(32);
	for(int i = 0; i< 32; ++i)
		test_strings[i]= "rRrRr_____________BRBBbbbb__Rrrr_b_bBB_RR_";

	vector<pair<double, string> > butt;
	butt = boardEval(test_strings, test2);
	for(size_t i =0; i<butt.size(); ++i)
		cout<<butt[i].first <<" | " << butt[i].second<< endl;

	writeNet(path, test2);
	return 0;
}
