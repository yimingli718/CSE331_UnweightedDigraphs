//
// Written by Sorrachai Yingchareonthawornchai, 29 OCT 2014
//
// Name :        main.cpp
// Description : Main program that reads an input file and builds a graph
//

#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include "UnweightedGraph.h"                // Edit your code in UnweightedGraph.h

using namespace std;


int main(int argc, char * argv[]) {
    if(argc != 2) {
        cout << "need input file" << endl;
        return 0;
    }
    UnweightedGraph G(argv[1]);
    G.DisplayInfo();
    cout << "G.IsConnected: " << G.IsConnected() << endl;
    cout << "G.IsEulerian: " <<G.IsEulerian() << endl;
    if(G.IsConnected() && G.IsEulerian()) {
        list<int> cycle = G.FindEulerianCycle();
        std::copy(begin(cycle),end(cycle),std::ostream_iterator<int>(std::cout," "));
        cout << endl;
        cout << "Verify cycle: " << G.VerifyEulerCycle(cycle) << endl;
    }
    //You may want to test for the false cycle to verify your verifyEulerCycle function too!
    
    return 0;
}
