#include "../lib/PAM.h"

PAM::PAM(void) : Update() {    
    cout << "PAM is being created" << endl;
}

PAM::~PAM(void) {
    cout << "PAM is being deleted" << endl;
}

void PAM::update(Initialization * init){
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

        init->getClusterItem(i)->updateCentroid(points->at(index)->getVectorID(), points->at(index)->getVectorDimension(), points->at(index)->getVectorCoordinates());
    }
    delete distance;
}

void PAM::update(Initialization * init, Distance * distance){
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

        init->getClusterItem(i)->updateCentroid(points->at(index)->getVectorID(), points->at(index)->getVectorDimension(), points->at(index)->getVectorCoordinates());
    }
}
