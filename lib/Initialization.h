#ifndef INITIALIZATION
#define INITIALIZATION

#include <iostream>
#include <cmath>
#include "Cluster.h"
#include <algorithm>
#include <chrono>
#include <iterator> 
#include <unordered_map> 

using namespace std;
using namespace std::chrono;

class Initialization {
    private:
        int numberOfClusters;
        Cluster *cluster;
    public:
        Initialization(int K);
        virtual ~Initialization(void);
        int getClusterSize(void); 
        Cluster * getClusterItem(int index);
        void clearClusterItems();
        vector <Vector *> * getCentroids(void);
};

#endif //INITIALIZATION
