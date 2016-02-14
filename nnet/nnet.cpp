#include "nnet.h"

#include <vector>
using std::vector;
#include <fstream>
using std::ifstream;
using std::ofstream;
#include <string>
using std::string;
#include <utility>
using std::pair;
#include <cstddef>
using std::size_t;
#include <queue>
using std::priority_queue;
#include <cmath>
using std::exp;
using std::fabs;

//function writeNet
//takes a string and a neural network
//writes nnet to given string
//returns bool
bool writeNet(const string & path, const vector<vector<double> > & nNet)
{
	ofstream netW(path.c_str());
	if(!netW)
		return false;
	else{	
		for(size_t i =0; i<nNet.size(); ++i){
			netW<< nNet[i].size()<< "\n";
			for(size_t j=0; j< nNet[i].size(); ++j)
				netW<< nNet[i][j] << " ";
			netW << "\n";
		}
	return true;
	}
	return false;
}	

//fucntion loadNet
//takes a string
//loads network from given file name
//throws (currently causes crash by doing so) if file is not found
//returns network (vector of vectors of doubles)
vector<vector<double> > loadNet(const string & path)
{
	size_t in1;
	size_t in;
	double in2;
	size_t count = 0;
	vector<vector<double> > rNet;
	ifstream netR(path.c_str());
	if(!netR)
		throw;
	else{
		while(!netR.eof()){
			netR>> in;
			vector<double> temp(in);
			rNet.push_back(temp);
			for(size_t i =0; i<in; ++i){
				netR>> in2;
				rNet[count][i]=in2;
				}
			count++;
		}
	}
	return rNet;
}

//function phi
//takes a double
//runs given double through the CDF for a normal Gaussian distrobution
//returns output of CDF
double phi(double x)
{
	    // constants
	    double a1 =  0.254829592;
	    double a2 = -0.284496736;
	    double a3 =  1.421413741;
	    double a4 = -1.453152027;
	    double a5 =  1.061405429;
	    double p  =  0.3275911;
	    
	    // Save the sign of x
	    int sign = 1;
	    if (x < 0)
	        sign = -1;
	    x = fabs(x)/sqrt(2.0);

            // A&S formula 7.1.26
            double t = 1.0/(1.0 + p*x);
            double y = 1.0 - (((((a5*t + a4)*t) + a3)*t + a2)*t + a1)*t*exp(-x*x);

	    return 0.5*(1.0 + sign*y);
}//CDF for Normal Distribution 
 //code found on www.johndcook.com/blog/cpp_phi/

//function activate
//takes vector of doubles
//sums values returned by phi
//returns sum as a double
double activate(const vector<double> & sum)
{
	double rd =0;
	for(size_t i = 0; i< sum.size(); ++i)
		rd+= phi(sum[i]);
	return rd;
}


//fuction boardPos
//takes string and a vector of doubles, returns nothing
//sets numbers in vector according to string
void boardPos(vector<double> & numBoard, const string & board)
{
	for(double i =0; i<32; ++i)
		numBoard[i]=phi(i*3); 
}
	
//funtion boardEval
//takes a two vectors
//one of stings, the other of vectors of doubles (neural network)
//evaluates boards bases on weights
//returns a priority queue containing the strings given and their calculated score
//priority_queue<double, string> boardEval(vector<string> & boards ,vector<vector<double> > & nNet)
//{
//	priority_queue<double, string> rBoards;
//	double score;
//	for(size_t o=0; o<boards.size(); ++o){
//		boardPos(nNet[0], boards[o]);
//			for(size_t i = 1; i<nNet.size(); ++i)
//				for(size_t j = 0; j<nNet[i].size(); ++j)
//					nNet[i][j]=activate(nNet[i-1]);
//		score = nNet[nNet.size()][nNet[nNet.size()].size()];
//		rBoards.push(score, boards[o]);
//	}	
//	return rBoards;
//}

//working version of boardEval, using a vector of pairs instead of priority_queue
//because i'm too dumb to figure out priorty queue right now
vector<pair<double, string> > boardEval(vector<string> & boards ,vector<vector<double> > & nNet)
{
	vector<pair<double, string> > rBoards(boards.size());
	double score;
	for(size_t o=0; o<boards.size(); ++o){
		boardPos(nNet[0], boards[o]);
			for(size_t i = 1; i<nNet.size(); ++i)
				for(size_t j = 0; j<nNet[i].size(); ++j){
					nNet[i][j]=activate(nNet[i-1]);
					if(nNet[i].size() == 1)
						score=nNet[i][j];
				}
		rBoards[o].first=score;
		rBoards[o].second=boards[o];
	}	
	return rBoards;
}


