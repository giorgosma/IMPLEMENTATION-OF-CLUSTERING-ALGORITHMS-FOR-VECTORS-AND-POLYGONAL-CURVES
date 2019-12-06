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
#include "./lib/Silhouette.h"
#include "./lib/RangeSearch.h"

using namespace std;
using namespace std::chrono;

double centroidDistance(Distance * calculator, vector<Vector *> * centroids){
    double dist = 0;
    for(int i=0; i<centroids->size()-1; i++){
        dist += calculator->calculateDistance(centroids->at(i), centroids->at(i+1));
    }
    return dist;
}

bool whatInputFile(string fileName) {
    string str;
    ifstream infile;
    infile.open(fileName);
    getline(infile, str);
    str = str.substr(0, 6);
    infile.close();
    if (str == "curves")
        return true;
    else
        return false;
}
// 1         2   3    4      5      6
// inputFile K init assign update complete
int main(int args, char **argv) {
    //curves
    vector<vector<double> *> * curves = NULL;
    VectorArray *vectorArray = NULL;
    //vectors

    bool isCurves = whatInputFile(argv[1]);
    if (isCurves) {
        CurvesParser parser;
        curves = parser.parseFile(argv[1]);
        vectorArray = parser.storeCurvesIntoVectorArray(curves);
    }
    else {
        Parser parser;
        parser.parseFileInput(argv[1]);
        vectorArray = parser.readFileInput(argv[1]);
    }
    // Parser parser;
    // parser.parseFileInput(argv[1]);
    // VectorArray *vectorArray = parser.readFileInput(argv[1]);

    int K = atoi(argv[2]);
    bool complete = false;
    if (atoi(argv[6]) == 1)
        complete = true;

    // Create distance calculating object
    Distance * distance;
    if(isCurves){
        distance = new DTW();
    }
    else{
        distance = new Manhattan();
    }

    // Initialize cluster centroids with RandomSelection/KMeans
    Initialization * initial;
    int initialSelection = atoi(argv[3]);
    if (initialSelection == 1)
        initial = new RandomSelection(K, vectorArray);
    else if (initialSelection == 2)
        initial = new KMeansInit(K, vectorArray);
    else {
        cout << "ERROR in Initial" << endl;
        return -1;
    }

    // Create assign and update objects
    Assignment * assign;
    int assignSelection = atoi(argv[4]);
    if (assignSelection == 1)
        assign = new Lloyds(distance);
    else if (assignSelection == 2) {
        if (isCurves)
            assign = new RangeSearch(3, 2, vectorArray, curves, distance);
        else 
            assign = new RangeSearch(3, vectorArray->getVectorArraySize() / 8, 4000, vectorArray->getVectorArrayItem(0)->getVectorDimension(), 4, vectorArray, distance);
    }
    else {
        cout << "ERROR in Assign" << endl;
        return -1;
    }
    Update * update;
    int updateSelection = atoi(argv[5]);
    if (updateSelection == 1)
        update = new PAM();
    else if (updateSelection == 2){
        if(isCurves){
            cout << "Mean Curves not implemented" << endl;
            return -1;
        }
        update = new MeanVector();
    }
    else {
        cout << "ERROR in Update" << endl;
        return -1;
    }


    // Calculate distance between the initial centroids
    vector<Vector *> * old_centroids = initial->getCentroids();
    double old_centroid_distance = centroidDistance(distance, old_centroids);

    int count = 0;
    while(count < 50){
        count++;

        // Assign points to clusters and update centroids
        initial->clearClusterItems();
        assign->setupAssignment(initial, vectorArray);
        assign->printClusterItems(initial);
        update->update(initial, distance);

        // Calculate distance between the newly selected centroids
        vector<Vector *> * new_centroids = initial->getCentroids();
        double new_centroid_distance = centroidDistance(distance, new_centroids);

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
    // call Silhouette
    Silhouette silhouette(initial, isCurves, complete);

    // Delete old centroids
    for(int i=0; i<old_centroids->size(); i++){
        delete old_centroids->at(i);
    }
    delete old_centroids;
    cout << "Loop count: " << count << endl;

    delete initial;
    delete vectorArray;
    delete distance;
    delete assign;
    delete update;
}
