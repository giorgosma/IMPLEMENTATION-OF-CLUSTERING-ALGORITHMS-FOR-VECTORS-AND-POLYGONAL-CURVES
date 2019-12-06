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
#include "./lib/MeanVector.h"

using namespace std;
using namespace std::chrono;

double centroidDistance(Distance * calculator, vector<Vector *> * centroids){
    double dist = 0;
    for(int i=0; i<centroids->size()-1; i++){
        dist += calculator->calculateDistance(centroids->at(i), centroids->at(i+1));
    }
    return dist;
}

int main(int args, char **argv) {

    // Parse input file
    Parser parser;
    parser.parseFileInput(argv[1]);
    VectorArray *vectorArray = parser.readFileInput(argv[1]);

    int K = 5;

    // Create distance calculating object
    Distance * manhattan = new Manhattan();

    // Initialize cluster centroids with RandomSelection/KMeans
    Initialization * initial = new RandomSelection(K, vectorArray);

    // Create assign and update objects
    Assignment * assign = new Lloyds();
    Update * update = new MeanVector();

    // Calculate distance between the initial centroids
    vector<Vector *> * old_centroids = initial->getCentroids();
    double old_centroid_distance = centroidDistance(manhattan, old_centroids);

    int count = 0;
    while(count < 2){
        count++;

        // Assign points to clusters and update centroids
        initial->clearClusterItems();
        assign->setupAssignment(initial, vectorArray);
        assign->printClusterItems(initial);
        update->update(initial, manhattan);

        // Calculate distance between the newly selected centroids
        vector<Vector *> * new_centroids = initial->getCentroids();
        double new_centroid_distance = centroidDistance(manhattan, new_centroids);

        // Check if centroid distance is within 0.1% if previous value
        bool terminateLoop;
        double diff = old_centroid_distance - new_centroid_distance;
        double diff_percentage = diff / old_centroid_distance;
        if(diff_percentage > -0.001 && diff_percentage < 0.001)
            terminateLoop = true;
        else terminateLoop = false;


        // Print details about old and new centroids
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

        // End loop if need be
        if(terminateLoop){
            break;
        }
    }

    // Delete old centroids
    for(int i=0; i<old_centroids->size(); i++){
        delete old_centroids->at(i);
    }
    delete old_centroids;
    cout << "Loop count: " << count << endl;

    delete initial;
    delete vectorArray;
    delete manhattan;
    delete assign;
    delete update;
}
