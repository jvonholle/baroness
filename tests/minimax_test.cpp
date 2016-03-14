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
    for(int i = 0; i < 99; ++i)
        w.push_back(i/(i*3+i)+(i/i*17));
    vector<size_t> l = {32,3,1};
    neuralNet tester(l,w);

    string startb = "rrrr__rr___r__b_rb___r_br__bb__b";
    auto first_kids = getBoardsN(startb, true);

    move head(startb, tester);
    head.make_kids(true);
   cout << "strings in head: " << endl; 
    for( auto & i : head.get_kids())
        cout << i->get_current() << endl;
   cout << "strings in first_kids: " << endl; 
    for(auto & i : first_kids)
        cout <<  i << endl;

    vector< pair< double, string > > weighed_kids;

    for( auto & i : head.get_kids())
        i->make_kids(false);

    for(int i = 0; i < first_kids.size(); ++i)
        weighed_kids.push_back(make_pair(tester.evaluate(first_kids[i]), first_kids[i]));

    sort(weighed_kids.begin(), weighed_kids.end());

    for(auto & i : weighed_kids)
        cout << "board string: " << i.second << " score: " << i.first << endl;

    for( auto & i : head.get_kids()){
        for(auto & j : i->get_kids())
            pick(*j, true);
       pick(*i, false); 
    }

    pick(head, true);

    //string picked = minimax(startb, tester, true,  3);
    
    cout << "head's string: " << head.get_current() << " head's score: " << head.get_score() << endl;
    for(auto & i : head.get_kids())
        cout << "kid string: " << i->get_current() << " kid score: " << i->get_score() << endl;

    //cout << endl << "Minimax pick: " << picked << endl;

    return 0;
}
