#include <iostream>
#include <cmath>
#include "Assignment.h"
#include "LSH.h"
#include "DTW.h"
#include "Grids.h"
#include <algorithm>
#include <chrono>
#include <random>
#include <iterator> 
#include <set> 
#include <unordered_map> 

using namespace std;
using namespace std::chrono;

struct arrayMap{
    unordered_map<int, vector<Cluster *>> umap; 
}arrayMap;

class RangeSearch : public Assignment{
    private:
        LSH **lsh;
        int lshSize;

        bool isCurve;
        VectorArray **vectorArray;
        long int vectorArraySize;
    public:
        RangeSearch(int L, int TableSize, int W, int dimensionSize, int k, VectorArray * vectors);
        RangeSearch(int k, int L_grids, VectorArray *curves, vector<vector<double> *> * veCurves);
        ~RangeSearch(void);
        void setupAssignment(Initialization * init, VectorArray * vectors);
        void initLSH(VectorArray * vectors);
        Cluster * getMinCluster(set<Cluster *> setOfClusters, Vector * vector);
        void setupAssignment(Initialization * init, vector<Vector *> vectors);
};