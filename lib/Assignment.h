#ifndef ASSIGNMENT
#define ASSIGNMENT

#include <iostream>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <iterator> 
#include <unordered_map> 

#include "Initialization.h" 
#include "VectorArray.h" 
#include "Distance.h" 
#include "Manhattan.h" 
#include "DTW.h" 

using namespace std;
using namespace std::chrono;

class Assignment {
    private:
    public:
        Assignment(void);
        virtual ~Assignment(void);
        virtual void setupAssignment(Initialization * init, VectorArray * vectors);
        // virtual void setupAssignment(Initialization * init, VectorArray * vectors);
        void printClusterItems(Initialization *init);
        bool isCentroid(Vector *vector, Initialization * init);
};

#endif //ASSIGNMENT