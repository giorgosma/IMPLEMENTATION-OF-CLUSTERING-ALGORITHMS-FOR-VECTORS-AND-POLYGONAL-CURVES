#ifndef PARSER
#define PARSER

#include <iostream>
#include <fstream>
#include <string>
#include "time.h"

#include "ExactNN.h"
#include "LSH.h"
//#include "HashFunction.h"
#include "VectorArray.h"
#include "ExactNN.h"
#include <algorithm>
#include <chrono>

using namespace std::chrono;
using namespace std;

class Parser {
    private:
        int vectorArraySize;
        int dimensionSize;
    public:
        Parser(void);
        ~Parser(void);
        void parseFileInput(string fileName);
        VectorArray *readFileInput(string fileName);
        string getFileItem(string str, int itemStart);
        int getVectorArraySize(void);
        int getDimensionSize(void);
};

#endif // PARSER