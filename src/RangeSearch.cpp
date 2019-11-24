#include "../lib/RangeSearch.h"

RangeSearch::RangeSearch(int L, int TableSize, int W, int dimensionSize, int k, VectorArray *vectors) : Assignment() {
    cout << "RangeSearch is being created" << endl;
    this->lsh = new LSH*[1];
    this->lsh[0] = new LSH(L, TableSize, W, dimensionSize, k);  
    this->isCurve = false;

    int counter = 0;
    for (int i = 0; i < vectors->getVectorArraySize(); i++) {
        this->lsh[0]->addItem(vectors->getVectorArrayItem(i));
        counter++;
        if (counter == 100) {
            cout << "ADDED " << i + 1 << " Vectors"<< endl;
            counter = 0;
        }
        if (i == vectors->getVectorArraySize() - 1)
            cout << "ADDED " << i + 1 << " Vectors"<< endl;
    }

    this->lshSize = 1;
}

RangeSearch::RangeSearch(int k, int L_grids, VectorArray *curves, vector<vector<double> *> * veCurves) : Assignment() {
    cout << "RangeSearch is being created" << endl;
    this->isCurve = true;

    Grids * grid = new Grids(L_grids, 0.01, 2);
    this->lshSize = L_grids;
    vector<vector<vector<double> *> *> * LGrids = grid->projectToGrids(veCurves);
    this->vectorArraySize = static_cast<int>(LGrids->size());
    VectorArray **vectorArray = new VectorArray*[LGrids->size()];
    this->lsh = new LSH*[LGrids->size()];
    for (int i = 0; i < (int)(LGrids->size()); i++) {
        vectorArray[i] = new VectorArray(LGrids->at(i)->size());
        this->lsh[i] = new LSH(1, (LGrids->at(i)->size())/8, 4000, LGrids->at(i)->at(0)->size(), k);
        for (int j = 0; j < (int)(LGrids->at(i)->size()); j++) {
            Vector *vector = new Vector(to_string(j), LGrids->at(i)->at(j)->size());
            double *dimension = new double[LGrids->at(i)->at(j)->size()];
            for (int k = 0; k < (int)(LGrids->at(i)->at(j)->size()); k++) {
                dimension[k] = LGrids->at(i)->at(j)->at(k);
            }
            vector->initVector(dimension);
            delete[] dimension;
            vectorArray[i]->addVectorToArray(vector, j);
            this->lsh[i]->addItem(vectorArray[i]->getVectorArrayItem(j));
            delete LGrids->at(i)->at(j);
        }
        delete LGrids->at(i);
    }
    this->vectorArray = vectorArray;
    // for (int i = 0; i < (int)(LGrids->size()); i++) {
    //     delete vectorArray[i];
    // }
    // delete[] vectorArray; 
    delete LGrids; 
    delete grid; 

}

RangeSearch::~RangeSearch(void) {
    cout << "RangeSearch is being deleted" << endl;
    if (this->isCurve) {
        for (int i = 0; i < this->vectorArraySize; i++) {
            delete this->vectorArray[i];
        }
        delete[] this->vectorArray;
    } 
    for (int i = 0; i < this->lshSize; i++) {
        delete this->lsh[i];
    }
    delete[] this->lsh;
}

void RangeSearch::initLSH(VectorArray * vectors) {
    for (int i = 0; i < vectors->getVectorArraySize(); i++) {
        this->lsh[0]->addItem(vectors->getVectorArrayItem(i));
    }
}

void RangeSearch::setupAssignment(Initialization * init, VectorArray * vectors) {
    for (int i = 0; i < this->lshSize; i++) {
        this->lsh[i]->printLSH();
    }
}