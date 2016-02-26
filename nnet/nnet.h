#ifndef NNET_H_INCLUDED
#define NNET_H_INLCUDED


#include <cstddef>
using std::size_t;
#include <vector>
using std::vector;

class neuralNet{
public:
    //Two param ctor
    //levels:
    //      a vector size_t's, stating the level layout eg: {32,40,10,1}
    //weights:
    //      a vector of doubles containing the weights for the net
    neuralNet(const vector<size_t> & levels, const vector<double> & weights);

    //      **PUBLIC MEMBER FUNCTIONS**      \\
    
    //evaluate
    //takes vector of doubles for level 0 input
    //doubles a, b, c are constants for sigmoid function 
    //returns double
    double evaluate(const vector<double> & input, const double a = 1, const double b = 2, const double c = 0);
    vector<size_t> getLevels(){
        return levels_;}

private:
    
    struct node_{
        vector<double> weights;
        double value;
    };
   
    void makeNodeLevels();
    void setWeights(const vector<double> & weights);

    vector<size_t> levels_;
    vector<vector<node_> > nodeLevels_;

};//END OF CLASS NNET
//EOF
#endif