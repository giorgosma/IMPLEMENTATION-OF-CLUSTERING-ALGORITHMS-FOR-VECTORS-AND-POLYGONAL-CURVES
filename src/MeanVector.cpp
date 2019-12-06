#include "../lib/MeanVector.h"

MeanVector::MeanVector(void) : Update() {    
    // cout << "MeanVector is being created" << endl;
}

MeanVector::~MeanVector(void) {
    // cout << "MeanVector is being deleted" << endl;
}

void MeanVector::update(Initialization * init){

    int size = init->getClusterItem(0)->getCentroid()->getSize();
    double * dimension = new double[size];

    // For each cluster
    for (int i = 0; i < init->getClusterSize(); i++) {
        // Get all cluster points
        vector<Vector *> * points = init->getClusterItem(i)->getItems();

        // Initialize dimension array
        for(int j=0; j<size; j++){
            dimension[j] = 0;
        }

        // Calculate mean vector
        for(int j=0; j<(int)points->size(); j++){
            double * temp = points->at(j)->getDimension();
            for(int k=0; k<size; k++){
                dimension[k] += temp[k] / (int)points->size();
            }
        }

        // for(int j=0; j<size; j++){
        //     cout << dimension[j] << ' ';
        // }
        // cout << endl << endl;

        init->getClusterItem(i)->updateCentroid(to_string(-1 * i), size, dimension);
    }

    delete dimension;
}


void MeanVector::update(Initialization * init, Distance * distance){

    int size = init->getClusterItem(0)->getCentroid()->getSize();
    double * dimension = new double[size];

    // For each cluster
    for (int i = 0; i < init->getClusterSize(); i++) {
        // Get all cluster points
        vector<Vector *> * points = init->getClusterItem(i)->getItems();

        // Initialize dimension array
        for(int j=0; j<size; j++){
            dimension[j] = 0;
        }

        // Calculate mean vector
        for(int j=0; j<(int)points->size(); j++){
            double * temp = points->at(j)->getDimension();
            for(int k=0; k<size; k++){
                dimension[k] += temp[k] / (int)points->size();
            }
        }

        // for(int j=0; j<size; j++){
        //     cout << dimension[j] << ' ';
        // }
        // cout << endl << endl;

        init->getClusterItem(i)->updateCentroid(to_string(-1 * i), size, dimension);
    }

    delete[] dimension;
}
