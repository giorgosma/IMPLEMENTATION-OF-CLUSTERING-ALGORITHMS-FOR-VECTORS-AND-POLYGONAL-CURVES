#ifndef EXACTNN
#define EXACTNN

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Manhattan.h"
#include "Parser.h"

using namespace std;

struct NeighborsArray {
    Manhattan *manhattanDistance;
    Vector *vector;
};

class ExactNN {
    private:
        VectorArray *pVectorArray;
        vector<NeighborsArray> neighborsArray;
        int rayDistance;
    public:
        ExactNN(VectorArray *vectorArray, int rayDistance = -1);
        ~ExactNN(void);
        vector<NeighborsArray> findExactNN(Vector *query, string outfile);
        void testVector(Vector *vector, Manhattan *manhattanDistance);
        void printNN(void);
        void addNeighbor(Vector *vector, Manhattan *manhattanDistance);
        void replaceNeighbor(Vector *vector, Manhattan *manhattanDistance);
        void writeNN(string fileName, Vector *query, double);
        void writeNNVerbose(string fileName, Vector *query, double);
};

#endif //EXACTNN