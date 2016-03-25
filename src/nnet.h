#ifndef NNET_H_INCLUDED
#define NNET_H_INLCUDED

#include <cstddef>
using std::size_t;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <functional>
using std::function;
#include <utility>
using std::pair;

class neuralNet{
public:
    //Two param ctor
    //levels:
    //      a vector size_t's, stating the level layout eg: {32,40,10,1}
    //weights:
    //      a vector of doubles containing the weights for the net
    neuralNet(const vector<size_t> & levels, const vector<double> & weights);

    //One param ctor
    //path:
    //    file path to network to load
    //throws if file cannot be opened
    //strong guarantee
    neuralNet(const string & path);

    //      **PUBLIC MEMBER FUNCTIONS**      \\
    
    //evaluate
    //takes vector of doubles for level 0 input
    //doubles a, b, c are constants for sigmoid function 
    //returns double
    double evaluate(const vector<double> & input, const double a = 1, const double b = 2, const double c = 0);
    double evaluate(const string & inputS, const double a = 1, const double b = 2, const double c = 0, bool red = true);

    //evolve
    //takes a string and a function
    //returns nothing
    //runs the function on weights in current net
    //saves to given filepath
    //throws if file cannot be opened
    //strong guarantee
    void evolve(const string & path, function<double(double)> evolver);

    //getLevels
    //takes nothing
    //returns levels
    vector<size_t> getLevels(){
        return levels_;}

    //go
    //takes a string
    //returns a string
    //evaluates and alpha betas its way to the best move then returns that
    //pair<string, bool> go(const string & board, bool red);
    pair<string,bool> go(const string & board, bool red, string & ab);

    //set score
    //used to make scoring more thread safe
    void set_score(const int & i){
        score=i;}

    //get score
    //used to make scoring more thread safe
    int get_score(){
        return score;}

private:
    
    struct node_{
        vector<double> weights;
        double value;
    };
   
    void makeNodeLevels();
    void setWeights(const vector<double> & weights);
    
    int score;

    vector<size_t> levels_;
    vector<vector<node_> > nodeLevels_;

};//END OF CLASS NNET
//EOF
#endif
