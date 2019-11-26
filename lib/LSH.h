#ifndef L_SH
#define L_SH

#include <iostream>
#include <vector>
#include "Manhattan.h"
#include "HashTable.h"
#include "Parser.h"

using namespace std;

class LSH {
    private:
        int L;
        vector<HashTable *> *LhashTables;
    public:
        LSH(int L, int TableSize, int w, int dimensionSize, int k);
        ~LSH(void);
        void printLSH(void);
        void addItem(Vector *vector);
        void addG(Vector * vector);
        Vector * getNN(Vector * vector);
        vector <Vector *> getNNBonus(Vector * vec, int r);
        vector<string> getBucketVectorsID(Vector * vec);
        int getIndex(int G);
        int getL();
};

#endif // LSH
