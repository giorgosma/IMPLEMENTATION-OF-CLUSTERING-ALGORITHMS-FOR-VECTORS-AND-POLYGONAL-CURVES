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

double centroidDistance(Distance * calculator, vector<Vector *> * centroids){
    double dist = 0;
    for(int i=0; i<centroids->size()-1; i++){
        dist += calculator->calculateDistance(centroids->at(i), centroids->at(i+1));
    }
    return dist;
}

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
    double old_centroid_distance;

    Assignment * assign = new Lloyds();
    Update * update = new PAM();

    Initialization * initial = new RandomSelection(K, vectorArray);
    old_centroids = initial->getCentroids();
    old_centroid_distance = centroidDistance(manhattan, old_centroids);
    assign->setupAssignment(initial, vectorArray);
    assign->printClusterItems(initial);

    int count = 0;
    while(count < 50){
        count++;
        update->update(initial);

        initial->clearClusterItems();
        assign->setupAssignment(initial, vectorArray);
        assign->printClusterItems(initial);

        vector<Vector *> * new_centroids = initial->getCentroids();
        double new_centroid_distance = centroidDistance(manhattan, new_centroids);

        bool terminateLoop = true;

        // // Check if centroids have the same IDs
        // for(int i=0; i<old_centroids->size(); i++){
        //     if(old_centroids->at(i)->getVectorID() != new_centroids->at(i)->getVectorID()){
        //         terminateLoop = false;
        //         break;
        //     }
        // }

        // Check if centroid distance is within 1% if previous value
        double diff = old_centroid_distance - new_centroid_distance;
        double diff_percentage = diff / old_centroid_distance;
        if(diff_percentage > -0.001 && diff_percentage < 0.001)
            terminateLoop = true;
        else terminateLoop = false;



        for(int i=0; i<old_centroids->size(); i++) cout << old_centroids->at(i)->getVectorID() << " ";
        cout << "    Total distance: " << old_centroid_distance << endl;
        for(int i=0; i<old_centroids->size(); i++) cout << new_centroids->at(i)->getVectorID() << " ";
        cout << "    Total distance: " << new_centroid_distance << endl;
        cout << "Distance difference: " << diff << endl;
        cout << "Distance difference percentage: " << diff_percentage << endl;



        // Delete old centroids
        for(int i=0; i<old_centroids->size(); i++){
            delete old_centroids->at(i);
        }
        old_centroids->clear();

        // Update old centroids with new centroids
        for(int i=0; i<new_centroids->size(); i++){
            old_centroids->push_back(new_centroids->at(i));
        }
        old_centroid_distance = new_centroid_distance;

        // Delete new centroids
        delete new_centroids;

        if(terminateLoop){
            break;
        }
    }
    
    for(int i=0; i<old_centroids->size(); i++){
        delete old_centroids->at(i);
    }
    delete old_centroids;
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
    delete update;
}
