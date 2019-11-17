#include <iostream>
#include <cmath>
#include "Vector.h"
#include <algorithm>
#include <chrono>
#include <iterator> 
#include <unordered_map> 

using namespace std;
using namespace std::chrono;

class DTW {
    private:
        double distance;
        unordered_map<string, double> array;

    public:
        DTW(void);
        ~DTW(void);
        double euclidean(vector<double> p, vector<double> q, int i, int j);
        double C(vector<double> p, vector<double> q, int i, int j);
        double getDTW(void);
        vector<double>  padding(vector<double> smallCurve, int bigSize);
        double calcDistance(vector<double> * p, vector<double> * q);
};