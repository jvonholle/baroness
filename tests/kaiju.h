#include "../src/minimax.h"
#include <memory>
using std::unique_ptr;
using std::move;

class kaiju{
    public:
    kaiju(const int & depth);
    
    pair<string, bool> go(const string & board, bool red);
    
    void set_score(const int & i){
        score_ = i;}
    int get_score(){
        return score_;}
    private:
    vector<unique_ptr<neuralNet>> eight_;
    vector<unique_ptr<neuralNet>> four_;
    unique_ptr<neuralNet> head_;
    unique_ptr<neuralNet> main_;
    unique_ptr<neuralNet> allinput_;
    int score_;
};

