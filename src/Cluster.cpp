#include "../lib/Cluster.h"

Cluster::Cluster(void) {    
    cout << "Cluster is being created" << endl;
}

Cluster::~Cluster(void) {
    // delete centroid;
    cout << "Cluster is being deleted" << endl;
    delete this->centroid;
}

void Cluster::initCluster(string id, int size, double *dimension){
    // this->clusterId = id;
    this->centroid = new Vector(id, size);
    this->centroid->initVector(dimension);

}

void Cluster::printClusterInfo(void) {
    cout << "Cluster Centroid: " << this->centroid->getVectorID() << endl;
    // this->centroid->printVector();
    cout << "   Cluster Size:" << this->clusterItems.size() << endl;
}

Vector * Cluster::getCentroid(void){
    return this->centroid;
}

void Cluster::addItemToCluster(Vector *item){
    this->clusterItems.push_back(item);
}