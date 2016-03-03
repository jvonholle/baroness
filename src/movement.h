//
//  movement.h
//  checkers
//
//
#ifndef checkers_movement_h
#define checkers_movement_h

#include <vector>
#include <string>
#include <utility>



//this may be misleading right now
typedef std::pair<int,std::string> bo; // used for boards with weights

//cSpaceN
//checks a position on a board to make sure its open
// takes an int pos: the position to check
bool cSpaceN(const bo & board, int pos);

//cJumpN
//takes 2 ints mPos: the position of the current peice
//  ePos: position of enemy to jump
//retunrs true if the jump can be made
bool cJumpN(const bo & board, int mPos, int ePos);

//mBoards
//takes a bo type board, int pos, int side , int di , and optional bool j
//the board is the original board to build from
//int pos is the peice to move
//int side is whice side is moving
//      side == 1 peice is moving down the board
//      side == 0 peice is moving up   the board
//      side == anything else moves up and down
//int di is the direction the peice is moving
//      di == 0 move down left
//      di == 1 move down right
//      di == 2 move up right
//      di == 3 move up left
//      di must be one of these values
//bool j is a flag that is set to true if the function call is after a jump
//
//retunrs a bo type that contains a board that has a move
bo mBoards(bo board,int pos, int side, int di ,bool j);

//getBoardsN
//takes a vector<bo> boards and int turn
//the vector passed to this function should have the origin board as its first element and no others
//int turn limits the peices that move
//      turn == 0 blacks turn
//      turn == 1 reds turn
std::vector<bo> getBoardsN(std::vector<bo> boards, int turn);





#endif
