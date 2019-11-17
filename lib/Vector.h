#ifndef VECTOR
#define VECTOR

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Vector {
    private:
        string id;
        long double *dimension;
        int size;
        

        vector<unsigned int> g;
    public:
        Vector(string id, int size);
        ~Vector(void);
        void initVector(long double *dimension);
        void printVector(void);
        int getVectorDimension(void);
        long double getVectorItem(int index);
        string getVectorID(void);
        void setG(unsigned int g);
        unsigned int getG(int index);
        long double * getVectorCoordinates();
};

#endif //VECTOR