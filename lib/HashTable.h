#ifndef HASHTABLE
#define HASHTABLE

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>

//#include "Vector.h"
#include "HashFunction.h"

using namespace std;

class HashTable {
    private:
        int size;
        vector<Vector *> * buckets;
        HashFunction *hashFunction;
    public:
        HashTable(int size, int w, int dimensionSize, int k);
        ~HashTable(void);
        void print(void);
        bool add(int bucket, Vector * pointer);
        vector<Vector *> * getBucket(int bucket);
        int getTableSize(void);
        void storeVector(Vector *vector, int Lnumber);
        void addG(Vector *vector);
        void accessHashTable(unsigned int g);
};

#endif //HASHTABLE
