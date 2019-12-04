#include <iostream>
#include <cmath>
#include "Update.h"
#include <algorithm>
#include <chrono>
#include <random>
#include <iterator> 
#include <unordered_map> 

using namespace std;
using namespace std::chrono;

class MeanVector : public Update{
    private:

    public:
        MeanVector(void);
        ~MeanVector(void);
        void update(Initialization * init);
        void update(Initialization * init, Distance * distance);
};
