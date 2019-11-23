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
    private:
        vector<vector<double> *> * curves;
    public:
        CurvesParser(void);
        ~CurvesParser(void);
        int countLines(char * fileName);
        string getNext(string line, int start, char breakChar);
        vector<double> * parseLine(string line);
        vector<vector<double> *> * parseFile(char * fileName);
        VectorArray * storeCurvesIntoVectorArray(vector<vector<double> *> * curves);
};

#endif // CURVESPARSER
