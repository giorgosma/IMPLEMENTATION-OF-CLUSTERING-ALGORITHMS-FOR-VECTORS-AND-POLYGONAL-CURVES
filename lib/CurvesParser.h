#ifndef CURVESPARSER
#define CURVESPARSER

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Grids.h"
#include "DTW.h"
#include "VectorArray.h"

using namespace std;

class CurvesParser {
    public:
        int countLines(char * fileName);
        string getNext(string line, int start, char breakChar);
        vector<double> * parseLine(string line);
        vector<vector<double> *> * parseFile(char * fileName);
};

#endif // CURVESPARSER
