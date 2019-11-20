#ifndef MANHATTAN
#define MANHATTAN

#include <iostream>
#include <cmath>
#include "VectorArray.h"
#include "Distance.h"

using namespace std;

class Manhattan  : public Distance{
    private:
        double distance;
    
    public:
        Manhattan();
        Manhattan(Vector *p, Vector *q);
        ~Manhattan(void);
        double calculateDistance(Vector *p, Vector *q);
        double getManhattan(void);
};

#endif //MANHATTAN