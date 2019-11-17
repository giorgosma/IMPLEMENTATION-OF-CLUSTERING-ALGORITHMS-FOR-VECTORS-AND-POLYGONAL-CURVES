#include <iostream>
#include "./lib/LSH.h"
#include "./lib/Initialization.h"
#include "./lib/RandomSelection.h"
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

    // for (int i = 0; i < vectorArray->getVectorArraySize(); i++) {
    //     Vector *v = vectorArray->getVectorArrayItem(i);
    //     v->printVector();
    // }
    


    // auto start = high_resolution_clock::now(); 
    // //HashFunction hashFunction(4000, 128, 4);
    // LSH lsh(atoi(argv[4]), parser.getVectorArraySize()/8, 4000, parser.getDimensionSize(), atoi(argv[3]));
    // //lsh.printLSH();
    // int counter = 0;
    // for (int i = 0; i < parser.getVectorArraySize(); i++) {
    //     // if (i < 2) {
    //         // lsh.addItem(vectorArray->getVectorArrayItem(i));
    //         // counter++;
    //     // }
    //     // if (counter == 100) {
    //     //     cout << "ADDED " << i + 1 << " Vectors"<< endl;
    //     //     counter = 0;
    //     // }
    // }

    // auto stop = high_resolution_clock::now(); 

    // auto duration = duration_cast<microseconds>(stop - start); 

    // cout << "LSH Time taken " << duration.count() << " microseconds" <<endl;

    // Parser parser2;
    // parser2.parseFileInput(argv[2]);
    // VectorArray * vectorArray2 = parser2.readFileInput(argv[2]);
    // //cout << vectorArray2->getVectorArraySize() << endl;

    // for(int i=0; i<vectorArray2->getVectorArraySize(); i++) {
    //     lsh.addG(vectorArray2->getVectorArrayItem(i));
    // }
    // int countTrue = 0;
    // vector<ExactNN>  exactNN(parser2.getVectorArraySize(), ExactNN(vectorArray, -1));
    // for(int i=0; i<vectorArray2->getVectorArraySize(); i++){
    //     Vector * lshVector = lsh.getNN(vectorArray2->getVectorArrayItem(i));
    //     vector<NeighborsArray> exactVector = exactNN[i].findExactNN(vectorArray2->getVectorArrayItem(i), "exactLSHPoints.txt");
    //     if (lshVector->getVectorID() == (exactVector[0].vector)->getVectorID())
    //         countTrue++;
    // }
    // cout << "Found " << countTrue << " True of 100" << endl;
    // if (atoi(argv[5]) > 0)
    // for(int i=0; i<vectorArray2->getVectorArraySize(); i++){
    //     lsh.getNNBonus(vectorArray2->getVectorArrayItem(i), atoi(argv[5]));
    // }

    // delete vectorArray;
    // delete vectorArray2;
    // return 0;

    // RandomSelection sel(3);
    // Initialization *initial = &sel;
    // initial->getClusterSize();


    Initialization * initial = new RandomSelection(3, vectorArray);
    // initial->getClusterSize();
    delete initial;
    delete vectorArray;
}