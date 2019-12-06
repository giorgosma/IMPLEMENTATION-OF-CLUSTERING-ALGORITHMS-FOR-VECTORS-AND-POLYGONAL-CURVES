#ifndef SILHOUETTE
#define SILHOUETTE

#include <iostream>
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
#include <vector>

using namespace std;

class Silhouette {
    private:
        vector<double> *sigma;
        vector<Vector *> *clusterItems;
        bool isCurve;
        Distance *distance;
    public:
        Silhouette(Initialization *init, bool isCurve, bool complete);
        ~Silhouette(void);
        double computeAlpha(Vector *vector);
        double computeBeta(Initialization *init, Vector *vector, Vector *centroid);
};

#endif //SILHOUETTE