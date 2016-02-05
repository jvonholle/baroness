#include "movecheck.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <utility>
using std::pair;


int main()
{
	int pos;
	while(pos!=-1){
	cout<< "input number: ";
	cin >> pos;

	pair<pair<int,int>, pair<int, int> > x = getMove(pos);

	cout<< x.first.first << " " << x.first.second << " | " << x.second.first << " " << x.second.second << endl;
	}

	return 0;
}
