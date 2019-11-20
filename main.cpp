#include <iostream>
#include "./lib/LSH.h"
#include "./lib/Initialization.h"
#include "./lib/RandomSelection.h"
#include "./lib/KMeansInit.h"
#include "./lib/Distance.h"
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

    Initialization * initial = new KMeansInit(3, vectorArray);

    Distance * distance = new Manhattan();
    cout << distance->calculateDistance(vectorArray->getVectorArrayItem(0), vectorArray->getVectorArrayItem(1)) << endl;
    delete distance;
    // initial->getClusterSize();
    delete initial;
    delete vectorArray;

}