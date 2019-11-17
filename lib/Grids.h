#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>

#include "LSH.h"
#include "HyperCube.h"

using namespace std;

class Grids {
    private:
        int L;
        double delta;
        vector<double> t;

    public:
        Grids(int, double, double);
        ~Grids(void);
        void printT();
        void generateT(double dimensionSize);
        vector<vector<vector<double> *> *> * projectToGrids(vector<vector<double> *> * curves);
        double accessGrid(vector<vector<vector<double> *> *> * grid, int L, int curveID, int p);
};
