#include "../lib/Lloyds.h"

Lloyds::Lloyds(Distance * distance) : Assignment() {
    cout << "Lloyds is being created" << endl;
    this->distance = distance;
}

Lloyds::~Lloyds(void) {
    cout << "Lloyds is being deleted" << endl;
}

void Lloyds::setupAssignment(Initialization * init, VectorArray * vectors) {
    int initCounter = 0;
    cout << "VectorArray = " << vectors->getVectorArraySize() << " ClusterSize " << init->getClusterSize() << endl;
    for (int i = 0; i < vectors->getVectorArraySize(); i++) {       // for each vector item
        // if (this->isCentroid(vectors->getVectorArrayItem(i), init)){
        //     // cout << "Vector " << vectors->getVectorArrayItem(i)->getVectorID() << endl;
        //     continue;
        // }
        double minDist = this->distance->calculateDistance(vectors->getVectorArrayItem(i), init->getClusterItem(0)->getCentroid());
        int indexCluster = 0;
        for (int j = 1; j < init->getClusterSize(); j++) {          // for each centroid - cluster
            double newDist = this->distance->calculateDistance(vectors->getVectorArrayItem(i), (init->getClusterItem(j))->getCentroid());
            if (minDist > newDist){
                minDist = newDist;
                indexCluster = j;  
            }
        }                                                         // store item to the minDist centroid - cluster
        init->getClusterItem(indexCluster)->addItemToCluster(vectors->getVectorArrayItem(i));
        initCounter++;
    }
}
