#ifndef CLUSTER
#define CLUSTER

#include <iostream>
#include <cmath>
#include "VectorArray.h"
#include <algorithm>
#include <chrono>
#include <iterator> 
#include <unordered_map> 

using namespace std;
using namespace std::chrono;

class Cluster {
    private:
        // string clusterId;
        Vector *centroid;

        vector<Vector *> clusterItems;
    public:
        Cluster(void);
        ~Cluster(void);
        void initCluster(string id, int size, double *dimension);
        void updateCentroid(string id, int size, double * dimension);
        void printClusterInfo(void);
        Vector * getCentroid(void);
        void addItemToCluster(Vector *item);
        vector<Vector *> * getItems(void);
        void clearClusterItems(void);
};

#endif //CLUSTER