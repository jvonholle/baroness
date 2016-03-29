#include "../src/minimax.h"

#include <iostream>
using std::cout; 
using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <utility>
using std::pair;
using std::make_pair;
#include <algorithm>
using std::sort;
#include <cstddef>
using std::size_t;

int main(){
    vector<double> w;
    w.resize(99, .3);
    vector<size_t> l = {32,3,1};
    neuralNet tester(l,w);

    string startb = "rrrrrrrr___r_r_b_________________";


    string picked = minimax(startb, tester, true); 
    string bpicked = minimax(picked, tester, false);
    

    cout << endl << "Minimax red pick: " << picked << endl;
    cout << "Minimax black pick: " << bpicked << endl;

    return 0;
}
