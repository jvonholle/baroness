#include <thrust/device_vector.h>
using thrust::device_vector;
#include <thrust/pair.h>
#include <chrono>
using std::chrono::steady_clock;
#include <map>
using std::map;
#include <utility>
using std::pair;
using std::make_pair;
#include <vector>
using std::vector;
#include <iostream>
#include "movecheck.h"

typedef pair<pair<int,int>, pair<int,int> > moves;
typedef thrust::pair<thrust::pair<int,int>, thrust::pair<int,int> > thrust_moves;


/*moves checkMap(int pos){
	map<int, moves> board;
board[0]= make_pair(make_pair(4,5),make_pair(-1,-1));
board[1]= make_pair(make_pair(5,6),make_pair(-1,-1));
board[2]= make_pair(make_pair(6,7),make_pair(-1,-1));
board[3]= make_pair(make_pair(7,-1),make_pair(-1,-1));
board[4]= make_pair(make_pair(8,-1),make_pair(0,-1));
board[5]= make_pair(make_pair(8,9),make_pair(1,-1));
board[6]= make_pair(make_pair(9,10),make_pair(2,1));
board[7]= make_pair(make_pair(10,11),make_pair(3,2));
board[8]= make_pair(make_pair(12,13),make_pair(5,4));
board[9]= make_pair(make_pair(13,14),make_pair(6,5));
board[10]= make_pair(make_pair(14,15),make_pair(7,6));
board[11]= make_pair(make_pair(15,-1),make_pair(7,-1));
board[12]= make_pair(make_pair(16,-1),make_pair(8,-1));
board[13]= make_pair(make_pair(16,17),make_pair(9,8));
board[14]= make_pair(make_pair(17,18),make_pair(10,9));
board[15]= make_pair(make_pair(18,19),make_pair(11,10));
board[16]= make_pair(make_pair(20,21),make_pair(13,12));
board[17]= make_pair(make_pair(21,22),make_pair(14,13));
board[18]= make_pair(make_pair(22,23),make_pair(15,14));
board[19]= make_pair(make_pair(23,-1),make_pair(15,-1));
board[20]= make_pair(make_pair(24,-1),make_pair(16,-1));
board[21]= make_pair(make_pair(24,25),make_pair(17,16));
board[22]= make_pair(make_pair(25,26),make_pair(18,17));
board[23]= make_pair(make_pair(26,27),make_pair(19,18));
board[24]= make_pair(make_pair(28,29),make_pair(21,20));
board[25]= make_pair(make_pair(29,30),make_pair(22,21));
board[26]= make_pair(make_pair(30,31),make_pair(23,22));
board[27]= make_pair(make_pair(-1,-1),make_pair(23,-1));
board[28]= make_pair(make_pair(-1,-1),make_pair(24,-1));
board[29]= make_pair(make_pair(-1,-1),make_pair(25,24));
board[30]= make_pair(make_pair(-1,-1),make_pair(26,25));
board[31]= make_pair(make_pair(-1,-1),make_pair(27,26));
board[-1]= make_pair(make_pair(-1,-1),make_pair(-1,-1));
return (board[pos]);
}*/



int main()
{

	device_vector<thrust_moves> dvec_board(32);
	
	auto b = steady_clock::now();
	for(int i=0; i<=31; ++i)
		dvec_board[i]=checkMap(i);
	auto e = steady_clock::now();
	auto diff = e-b;
	std::cout <<"dvec_gen: " << std::chrono::duration <double> (diff).count() << std::endl;

	auto b2 = steady_clock::now();
	for(int i = 0; i<1000000; ++i)
		auto temp = dvec_board[i%31];
	auto e2 = steady_clock::now();
	auto diff2 = e2-b2;
	std::cout <<"device_vector: " << std::chrono::duration <double> (diff2).count() << std::endl;

	int test=0;
	while(test!=666){
		std::cin>>test;
		thrust_moves temp = dvec_board[test];
		std::cout<< temp.first.first << " " << temp.first.second <<" || " << temp.second.first << " " << temp.second.second<< std::endl;}
}


