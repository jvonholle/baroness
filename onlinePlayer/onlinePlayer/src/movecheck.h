#ifndef CHECKMOVE_H_INCLUDED
#define CHECKMOVE_H_INCLUDED
#include <map>
using std::map;
#include <utility>
using std::pair;
using std::make_pair;

typedef pair<pair<int,int>, pair<int,int> > moves;

moves checkMap(int pos)
{
	map<int, moves> board;
	board[0]= make_pair(make_pair(4,5),make_pair(-1,-1));
	board[1]= make_pair(make_pair(5,6),make_pair(-1,-1));
	board[2]= make_pair(make_pair(6,7),make_pair(-1,-1));
	board[3]= make_pair(make_pair(7,-1),make_pair(-1,-1));
	board[4]= make_pair(make_pair(-1,8),make_pair(-1,0));
	board[5]= make_pair(make_pair(8,9),make_pair(0,1));
	board[6]= make_pair(make_pair(9,10),make_pair(1,2));
	board[7]= make_pair(make_pair(10,11),make_pair(2,3));
	board[8]= make_pair(make_pair(12,13),make_pair(4,5));
	board[9]= make_pair(make_pair(13,14),make_pair(5,6));
	board[10]= make_pair(make_pair(14,15),make_pair(6,7));
	board[11]= make_pair(make_pair(15,-1),make_pair(7,-1));
	board[12]= make_pair(make_pair(-1,16),make_pair(-1,8));
	board[13]= make_pair(make_pair(16,17),make_pair(8,9));
	board[14]= make_pair(make_pair(17,18),make_pair(9,10));
	board[15]= make_pair(make_pair(18,19),make_pair(10,11));
	board[16]= make_pair(make_pair(20,21),make_pair(12,13));
	board[17]= make_pair(make_pair(21,22),make_pair(13,14));
	board[18]= make_pair(make_pair(22,23),make_pair(14,15));
	board[19]= make_pair(make_pair(23,-1),make_pair(15,-1));
	board[20]= make_pair(make_pair(-1,24),make_pair(-1,16));
	board[21]= make_pair(make_pair(24,25),make_pair(16,17));
	board[22]= make_pair(make_pair(25,26),make_pair(17,18));
	board[23]= make_pair(make_pair(26,27),make_pair(18,19));
	board[24]= make_pair(make_pair(28,29),make_pair(20,21));
	board[25]= make_pair(make_pair(29,30),make_pair(21,22));
	board[26]= make_pair(make_pair(30,31),make_pair(22,23));
	board[27]= make_pair(make_pair(31,-1),make_pair(23,-1));
	board[28]= make_pair(make_pair(-1,-1),make_pair(-1,24));
	board[29]= make_pair(make_pair(-1,-1),make_pair(24,25));
	board[30]= make_pair(make_pair(-1,-1),make_pair(25,26));
	board[31]= make_pair(make_pair(-1,-1),make_pair(26,27));
	board[-1]= make_pair(make_pair(-1,-1),make_pair(-1,-1));
	
	if(pos<0 || pos >31){
		return (board[-1]);}

	return (board[pos]);

}


#endif
