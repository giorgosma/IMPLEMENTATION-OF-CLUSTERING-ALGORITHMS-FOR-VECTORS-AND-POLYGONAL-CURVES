#ifndef DISTANCE
#define DISTANCE

#include <iostream>
#include "VectorArray.h"

using namespace std;

class Distance {
    private:
    
    public:
        Distance(void);
        virtual ~Distance(void);
        virtual double calculateDistance(Vector *p, Vector *q);
        virtual double calculateDistance(vector<double> * p, vector<double> * q);
};

#endif //DISTANCE