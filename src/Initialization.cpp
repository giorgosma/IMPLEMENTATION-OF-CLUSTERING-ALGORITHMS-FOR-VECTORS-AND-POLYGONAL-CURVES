#include "../lib/Initialization.h"

Initialization::Initialization(int K) {    
    // cout << "Initialization is being created" << endl;
    this->numberOfClusters = K;
    this->cluster = new Cluster[K];
}

Initialization::~Initialization(void) {
    // cout << "Initialization is being deleted" << endl;
    delete[] this->cluster;
}

int Initialization::getClusterSize(void) {
    // cout << "Initialization ClusterSize " << this->numberOfClusters << endl;
    return this->numberOfClusters;
}

Cluster * Initialization::getClusterItem(int index) {
    return &(this->cluster[index]);
}

void Initialization::clearClusterItems(){
    for(int i=0; i<this->numberOfClusters; i++){
        this->cluster[i].clearClusterItems();
    }
}

vector<Vector *> * Initialization::getCentroids(void){
    vector<Vector *> * centroids = new vector<Vector *>;
    for(int i=0; i<this->numberOfClusters; i++){
        Vector * temp = this->cluster[i].getCentroid();
        Vector * cent = new Vector(temp->getID(), temp->getSize());
        cent->initVector(temp->getDimension());
        centroids->push_back(cent);
    }
    return centroids;
}
