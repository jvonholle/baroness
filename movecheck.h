#ifndef CHECKMOVE_H_INCLUDED
#define CHECKMOVE_H_INCLUDED
#include <map>
using std::map;
#include <utility>
using std::pair;
using std::makepair;

typedef pair<pair<int,int>, pair<int,int>> moves;

moves getMove(int pos)
{
	map<int, moves> board;
	board[0]= makepair(makepair(4,5),makepair(-1,-1));
	board[1]= makepair(makepair(5,6),makepair(-1,-1));
	board[2]= makepair(makepair(6,7),makepair(-1,-1)
	board[3]= makepair(makepair(7,-1),makepair(-1,-1));
	board[4]= makepair(makepair(8,-1),makepair(0,-1));
	board[5]= makepair(makepair(8,9),makepair(1,-1));
	board[6]= makepair(makepair(9,10),makepair(2,1));
	board[7]= makepair(makepair(10,11),makepair(3,2));
	board[8]= makepair(makepair(12,13),makepair(5,4));
	board[9]= makepair(makepair(13,14),makepair(6,5));
	board[10]= makepair(makepair(14,15),makepair(7,6));
	board[11]= makepair(makepair(15,-1),makepair(7,-1));
	board[12]= makepair(makepair(16,-1),makepair(8,-1));
	board[13]= makepair(makepair(16,17),makepair(9,8));
	board[14]= makepair(makepair(17,18),makepair(10,9));
	board[15]= makepair(makepair(18,19),makepair(11,10));
	board[16]= makepair(makepair(20,21),makepair(13,12));
	board[17]= makepair(makepair(21,22),makepair(14,13));
	board[18]= makepair(makepair(22,23),makepair(15,14));
	board[19]= makepair(makepair(23,-1),makepair(15,-1));
	board[20]= makepair(makepair(24,-1),makepair(16,-1));
	board[21]= makepair(makepair(24,25),makepair(17,16));
	board[22]= makepair(makepair(25,26),makepair(18,17));
	board[23]= makepair(makepair(26,27),makepair(19,18));
	board[24]= makepair(makepair(28,29),makepair(21,20));
	board[25]= makepair(makepair(29,30),makepair(22,21));
	board[26]= makepair(makepair(30,31),makepair(23,22));
	board[27]= makepair(makepair(-1,-1),makepair(23,-1));
	board[28]= makepair(makepair(-1,-1),makepair(24,-1));
	board[29]= makepair(makepair(-1,-1),makepair(25,24));
	board[30]= makepair(makepair(-1,-1),makepair(26,25));
	board[31]= makepair(makepair(-1,-1),makepair(27,26));

	return (board[pos])

}
