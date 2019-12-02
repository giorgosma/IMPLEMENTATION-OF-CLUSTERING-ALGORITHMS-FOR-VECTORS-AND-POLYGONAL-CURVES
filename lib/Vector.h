#ifndef VECTOR
#define VECTOR

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Vector {
    private:
        string id;
        double *dimension;
        int size;
        

        vector<unsigned int> g;
    public:
        Vector(string id, int size);
        ~Vector(void);
        void initVector(double *dimension);
        void printVector(void);
        int getVectorDimension(void);
        double getVectorItem(int index);
        string getVectorID(void);
        void setG(unsigned int g);
        unsigned int getG(int index);
        double * getVectorCoordinates();
        vector<unsigned int> * getG();
        double * getDimension();
};

#endif //VECTOR
