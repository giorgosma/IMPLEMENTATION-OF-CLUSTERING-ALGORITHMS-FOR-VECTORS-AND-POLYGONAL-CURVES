#include <iostream>
#include <cmath>
#include "Initialization.h"
#include <algorithm>
#include <chrono>
#include <random>
#include <iterator> 
#include <unordered_map> 

using namespace std;
using namespace std::chrono;

class RandomSelection : public Initialization{
    private:

    public:
        RandomSelection(int K, VectorArray *vectorArray);
        ~RandomSelection(void);

        // void getClusterSize(void);
};