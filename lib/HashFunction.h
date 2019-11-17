#ifndef HASH_FUNCTION
#define HASH_FUNCTION

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <chrono>

#include "Vector.h"

using namespace std;

class HashFunction {
    private:
        vector<double> *s;
        vector<double> *h;
        vector<int> a;
        int w;
        int k;
    public:
        HashFunction(int w, int dimensionSize, int k);
        ~HashFunction(void);
        void MakeRandomSI(int index, int dimensionSize, double w);
        int constructHI(int indexK);
        void constructAI(Vector *vector, int indexK);
        unsigned int constructG(void);
        void printSI(int indexK);
        void printAI(void);
        int printSize(void);
        void clearKHI();
        void getHashG(Vector *vector);
};

#endif //HASH_FUNCTION