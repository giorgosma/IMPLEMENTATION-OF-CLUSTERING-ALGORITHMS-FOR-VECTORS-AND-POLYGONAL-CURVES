#include <iostream>
#include <chrono>
#include <algorithm>

#include "./lib/LSH.h"
#include "./lib/Initialization.h"
#include "./lib/RandomSelection.h"
#include "./lib/KMeansInit.h"
#include "./lib/Distance.h"
#include "./lib/DTW.h"
#include "./lib/Assignment.h"
#include "./lib/Lloyds.h"
#include "./lib/CurvesParser.h"
#include "./lib/Update.h"
#include "./lib/PAM.h"

using namespace std;
using namespace std::chrono;

// inputFile queryFile k L r
// k=4 L=5 r=-1
//  1          2       3 4 5

int main(int args, char **argv) {

    // POINTS
    Parser parser;
    parser.parseFileInput(argv[1]);
    VectorArray *vectorArray = parser.readFileInput(argv[1]);

    // CURVES
    // CurvesParser parser;
    // vector<vector<double> *> * curves = parser.parseFile(argv[1]);
    // VectorArray *vectorArray = parser.storeCurvesIntoVectorArray(curves);
    // Distance * manhattan = new DTW();

    // cout << "DIST C " << manhattan->calculateDistance(curves->at(0), curves->at(2)) << endl;
    // cout << "DIST V " << manhattan->calculateDistance(vectorArray->getVectorArrayItem(0), vectorArray->getVectorArrayItem(2)) << endl;


    int K = 5;

    Distance * manhattan = new Manhattan();

    // // Initialization * initial = new KMeansInit(K, vectorArray);
    // Initialization * initial = new KMeansInit(K, vectorArray, manhattan);

    // // Print distances
    // double max = 0;
    // double min = 1000000000;
    // double avg = 0;
    // double count = 0;
    // for(int i=0; i<K; i++){
    //     for(int j=0; j<K; j++){
    //         if(i>=j) continue;
    //         double dist = manhattan->calculateDistance(initial->getClusterItem(i)->getCentroid(), initial->getClusterItem(j)->getCentroid());
    //         cout << "dist(" << i << ", " << j << "): " << dist << endl;

    //         avg += dist;
    //         count++;
    //         if(dist<min) min = dist;
    //         if(dist>max) max = dist;
    //     }
    // }


    // avg /= count;
    // cout << "Maximum Distance: " << max << endl;
    // cout << "Minimum Distance: " << min << endl;
    // cout << "Average Distance: " << avg << endl;


    vector<Vector *> * old_centroids;
    vector<Vector *> * new_centroids;

    Assignment * assign = new Lloyds();
    Update * update = new PAM();

    Initialization * initial = new RandomSelection(K, vectorArray);
    old_centroids = initial->getCentroids();
    assign->setupAssignment(initial, vectorArray);
    assign->printClusterItems(initial);

    int count = 0;
    while(count < 5){
        count++;
        update->update(initial);

        initial->clearClusterItems();
        assign->setupAssignment(initial, vectorArray);
        assign->printClusterItems(initial);

        new_centroids = initial->getCentroids();

        for(int i=0; i<old_centroids->size(); i++) cout << old_centroids->at(i)->getVectorID() << endl;
        for(int i=0; i<old_centroids->size(); i++) cout << new_centroids->at(i)->getVectorID() << endl;

        bool allSame = true;
        for(int i=0; i<old_centroids->size(); i++){
            if(old_centroids->at(i)->getVectorID() != new_centroids->at(i)->getVectorID()){
                allSame = false;
                break;
            }
        }
        if(allSame){
            break;
        }

        old_centroids->clear();
        for(int i=0; i<new_centroids->size(); i++){
            old_centroids->push_back(new_centroids->at(i));
        }
        delete new_centroids;
    }

    cout << "Loop count: " << count << endl;

    // update->update(initial);
    // initial->clearClusterItems();
    // assign->setupAssignment(initial, vectorArray);
    // assign->printClusterItems(initial);

    // update->update(initial);
    // initial->clearClusterItems();
    // assign->setupAssignment(initial, vectorArray);
    // assign->printClusterItems(initial);

    // update->update(initial);
    // initial->clearClusterItems();
    // assign->setupAssignment(initial, vectorArray);
    // assign->printClusterItems(initial);

    delete initial;
    delete vectorArray;
    delete manhattan;
    delete assign;

}
