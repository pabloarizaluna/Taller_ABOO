#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <streambuf>
#include <string>
#include <list>
#include <iomanip>

#include "OptBinTree.h"

void BruteForceBackTracking(std::vector< std::vector<int> >P);
int main(int argc, char const *argv[]) {

        std::vector< std::vector<int> >P = {{-1, -1, -1, -1, -1, -1},
                                            {-1,  0,  0,  1,  1,  1},
                                            {-1, -1,  1,  1,  1,  3},
                                            {-1, -1, -1,  2,  3,  4},
                                            {-1, -1, -1, -1,  3,  4},
                                            {-1, -1, -1, -1, -1,  4}};
        BruteForceBackTracking(P);
        return 0;
}

void BruteForceBackTracking(std::vector< std::vector<int> >P){
        OptBinTree<int> tree  = OptBinTree<int>();
        for (int i = 1; i < P.size(); i++) {
                for (int j = P.size()-1; j >=  i; j--) {
                        tree.insert(P[i][j]);
                }
        }
        tree.preOrden();

}
