#include "../src/minimax.h"
#include <memory>
using std::unique_ptr;
using std::move;
#include <functional>
using std::function;

class kaiju{
    public:
    explicit kaiju(const char & useless);
    explicit kaiju(const int & count);
    
    pair<string, bool> go(const string & board, bool red);
    
    bool evolve(const int & count, function<double(double)> evolver, const int & cuttoff = 0);
    
    void set_score(const int & i){
        score_ += i;}
    int get_score(){
        return score_;}
    void reset_score(){
        score_ = 0;
    }
    private:
    vector<unique_ptr<neuralNet>> eight_;
    vector<unique_ptr<neuralNet>> four_;
    unique_ptr<neuralNet> head_;
    unique_ptr<neuralNet> main_;
    unique_ptr<neuralNet> allinput_;
    int score_ = 0;
};

