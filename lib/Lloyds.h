#include <iostream>
#include <cmath>
#include "Assignment.h"
#include <algorithm>
#include <chrono>
#include <random>
#include <iterator> 
#include <unordered_map> 

using namespace std;
using namespace std::chrono;

class Lloyds : public Assignment{
    private:
        bool isCurve;
    public:
        Lloyds(bool isCurve);
        ~Lloyds(void);
        void setupAssignment(Initialization * init, VectorArray * vectors);
};