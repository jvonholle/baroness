#include "minimax.h"
#include <algorithm>
using std::sort;

void pick(move & board, bool max){
    if(board.get_kids().size() <= 0)
        return;
    for(int i = 0; i < board.get_kids().size(); ++i)
        board.get_kids()[i]->set_score(board.get_net()->evaluate(board.get_kids()[i]->get_current()));

    if(max){
        board.set_score(-1000);
        for(int i = 0; i < board.get_kids().size(); ++i)
            if(board.get_kids()[i]->get_score() > board.get_score())
               board.set_score(board.get_kids()[i]->get_score());
        
    }else{
        board.set_score(1000);
        for(int i = 0; i < board.get_kids().size(); ++i)
            if(board.get_kids()[i]->get_score() < board.get_score())
               board.set_score(board.get_kids()[i]->get_score());
    }
}

string minimax(string board_start, neuralNet & net, bool red, int depth){
    move head(board_start, net);
    head.make_kids(red);
    
   return "end"; 
    
}
