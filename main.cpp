#include <iostream>
#include "./lib/LSH.h"
#include "./lib/Initialization.h"
#include "./lib/RandomSelection.h"
#include "./lib/KMeansInit.h"
#include "./lib/Distance.h"
#include "./lib/DTW.h"
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;

// inputFile queryFile k L r
// k=4 L=5 r=-1
//  1          2       3 4 5

int main(int args, char **argv) {
    Parser parser;
    parser.parseFileInput(argv[1]);
    VectorArray *vectorArray = parser.readFileInput(argv[1]);

    int K = 5;

    Distance * manhattan = new Manhattan();

    // Initialization * initial = new KMeansInit(K, vectorArray);
    Initialization * initial = new KMeansInit(K, vectorArray, manhattan);

    // Print distances
    for(int i=0; i<K; i++){
        for(int j=0; j<K; j++){
            if(i>=j) continue;
            cout << "dist(" << i << ", " << j << "): " << manhattan->calculateDistance(initial->getClusterItem(i)->getCentroid(), initial->getClusterItem(j)->getCentroid()) << endl;
        }
    }

    delete manhattan;
    delete initial;
    delete vectorArray;

}