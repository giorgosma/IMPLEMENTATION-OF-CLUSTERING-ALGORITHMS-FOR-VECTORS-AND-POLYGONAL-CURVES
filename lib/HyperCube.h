#include <iostream>
#include <iterator> 
#include <unordered_map> 
#include <map> 

#include "HashFunction.h"
#include "Parser.h"

using namespace std;

class HyperCube {
    private:
        int dimension;
        int k;
        int w;
        int M;
        int probes;

        int dTon;
        int size;
        unordered_map<string, vector<Vector *>> HashTable; // 0101, Bucket of Vectors
        HashFunction *hashFunction;
        map<unsigned int,unsigned int> *fArray;

    
    public:
        HyperCube(int dimensionSize, int w, int k, int dTon, int M, int probes);
        ~HyperCube(void);
        void insertNewVector(Vector *vector);
        void accessVerticle(Vector *vector);
        string getVerticle(Vector *vector);
        void printHashTableSize();
        void constructVerticle(Vector *vector);
        Vector * getNN(Vector *query);
        string getNeighborVerticle(string verticle, int index);
        vector <Vector *> getNNBonus(Vector * vec, int r);
        vector<string> getBucketVectorsID(Vector * query);
};