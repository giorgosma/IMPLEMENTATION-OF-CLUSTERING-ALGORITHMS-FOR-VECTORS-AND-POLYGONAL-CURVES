#ifndef VECTOR_ARRAY
#define VECTOR_ARRAY

#include <iostream>
#include "Vector.h"

using namespace std;

class VectorArray {
    private:
        int size;
        Vector **vectorArray;
    public:
        VectorArray(int size);
        ~VectorArray(void);
        void addVectorToArray(Vector *vector, int index);
        void printVectorArray(void);
        Vector *getVectorArrayItem(int index);
        int getVectorArraySize(void);
        Vector ** getVectorArray(void);
};

#endif //VECTOR_ARRAY