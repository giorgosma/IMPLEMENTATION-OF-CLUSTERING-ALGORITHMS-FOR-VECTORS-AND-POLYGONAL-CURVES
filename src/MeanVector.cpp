#include "../lib/MeanVector.h"

MeanVector::MeanVector(void) : Update() {    
    cout << "MeanVector is being created" << endl;
}

MeanVector::~MeanVector(void) {
    cout << "MeanVector is being deleted" << endl;
}

void MeanVector::update(Initialization * init){
    Distance * distance = new Manhattan();

    // For each cluster
    for (int i = 0; i < init->getClusterSize(); i++) {
        // Get pointer to points of cluster
        vector<Vector *> * points = init->getClusterItem(i)->getItems();
        vector<double> * dist = new vector<double>;

        for(int j=0; j<(int)points->size(); j++){
            dist->push_back(0);
            for(int k=0; k<(int)points->size(); k++){
                if(j == k) continue;
                dist->back() = dist->back() + distance->calculateDistance(points->at(j), points->at(k));
            }
        }

        double min = dist->at(0);
        int index = 0;
        for(int j=1; j<(int)dist->size(); j++){
            if(dist->at(j) < min){
                min = dist->at(j);
                index = j;
            }
        }

        delete dist;

        // cout << "Cluster #" << i << " minimum is " << index << ": " << min << endl;
        // for(int j=0; j<dist->size(); j++){
        //     cout << j << ") " << dist->at(j) << endl;
        // }

        // init->getClusterItem(i)->updateCentroid(string id, int size, double * dimension);
        init->getClusterItem(i)->updateCentroid(points->at(index)->getVectorID(), points->at(index)->getVectorDimension(), points->at(index)->getVectorCoordinates());
    }
    delete distance;
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
                dimension[k] += temp[k] / size;
            }
        }

        for(int j=0; j<size; j++){
            cout << dimension[j] << endl;
        }
        cout << endl;

        init->getClusterItem(i)->updateCentroid(to_string(-1 * i), size, dimension);
    }

    delete dimension;
}
