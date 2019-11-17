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
        Vector *clusterCoordinates;

        vector<Vector *> clusterItems;
    public:
        Cluster(void);
        ~Cluster(void);
        void initCluster(string id, int size, long double *dimension);
        void printClusterInfo(void);
};

#endif //CLUSTER