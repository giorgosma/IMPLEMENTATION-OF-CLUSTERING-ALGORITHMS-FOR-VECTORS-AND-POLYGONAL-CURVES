#ifndef MANHATTAN
#define MANHATTAN

#include <iostream>
#include <cmath>
#include "VectorArray.h"

using namespace std;

class Manhattan {
    private:
        int distance;
    
    public:
        Manhattan(Vector *p, Vector *q);
        ~Manhattan(void);
        void calculateDistance(Vector *p, Vector *q);
        int getManhattan(void);
};

#endif //MANHATTAN