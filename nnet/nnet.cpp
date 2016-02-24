//source file for nnet.h
//all definitions in header file
#include "nnet.h"

#include <cmath>
using std::exp;
#include <string>
using std::string;
#include <stdexcept>
using std::runtime_error;

double sigmoid(double sum, const double a, double b, const double c){
    if(b==0)
        b=1;
    if(sum < 0)
        return (a/(1.0+exp(sum/b)))+c;
    else
        return (a/(1.0+exp((sum*-1))))+c;
}

neuralNet::neuralNet(const vector<size_t> & levels, const vector<double> & weights):levels_(levels)
{
    if(levels_.size()<=0)
        throw runtime_error("Need more levels!");

    if(levels_.back()!=1)
        throw runtime_error("Too many nodes in last level! Expected 1, got "+ std::to_string(levels_.back()) + "!");

   makeNodeLevels();
   setWeights(weights);
}

double neuralNet::evaluate(const vector<double> & input, const double a, const double b, const double c){
    for(size_t i = 0; i < nodeLevels_[0].size(); ++i)
        nodeLevels_[0][i].value = input[i];

    for(size_t i = 1; i < nodeLevels_.size(); ++i){
        for(size_t j = 0; j < nodeLevels_[i].size(); ++j){
            double temp = 0;
                for(size_t k = 0; k <nodeLevels_[i-1].size(); ++k)
                    temp += nodeLevels_[i-1][k].value * nodeLevels_[i-1][k].weights[j];

            nodeLevels_[i][j].value = sigmoid(temp, a, b, c);
                }
       }

       return nodeLevels_[nodeLevels_.size()-1][0].value;
}

void neuralNet::makeNodeLevels(){
    nodeLevels_.clear();

    for(size_t i = 0; i < levels_.size(); ++i){
        if(i + 1 < levels_.size()){
            vector<node_> nodeLevel;

            for(size_t j = 0; j < levels_[i]; ++j){
                node_ node;
                node.value = 0;
                node.weights.resize(levels_[i+1], 1);
                nodeLevel.push_back(node);
            }

            nodeLevels_.push_back(nodeLevel);
        }
        else{
            node_ node;
            node.value = 5;
            node.weights.clear();
            nodeLevels_.push_back({node});
        }
    }
}

void neuralNet::setWeights(const vector<double> & weights){
    vector<double*> realWeights;

    for(auto & level:nodeLevels_)
        for(auto & node:level)
            for(auto & weight:node.weights)
                realWeights.push_back(&weight);

    if(weights.size() < realWeights.size())
        throw runtime_error("Not enough weights! Got " + std::to_string(weights.size()) + ", but I need " + std::to_string(realWeights.size()));
    else if(weights.size() > realWeights.size())
        throw runtime_error("Too many weights! Got " + std::to_string(weights.size()) + ", but I need " + std::to_string(realWeights.size()));

    for(size_t i = 0; i < realWeights.size(); ++i)
        *(realWeights[i]) = weights[i];
}
