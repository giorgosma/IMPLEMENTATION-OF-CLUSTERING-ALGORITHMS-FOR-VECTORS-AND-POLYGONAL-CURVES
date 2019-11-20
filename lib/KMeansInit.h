#include <iostream>
#include <cmath>
#include "Initialization.h"
#include "Distance.h"
#include "Manhattan.h"
#include <algorithm>
#include <chrono>
#include <random>
#include <iterator> 
#include <unordered_map> 

using namespace std;
using namespace std::chrono;

class KMeansInit : public Initialization{
    private:

    public:
        KMeansInit(int K, VectorArray *vectorArray);
        ~KMeansInit(void);

        // void getClusterSize(void);
};