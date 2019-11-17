#include "../lib/Cluster.h"

Cluster::Cluster(void) {    
    cout << "Cluster is being created" << endl;
}

Cluster::~Cluster(void) {
    // delete clusterCoordinates;
    cout << "Cluster is being deleted" << endl;
    delete this->clusterCoordinates;
}

void Cluster::initCluster(string id, int size, long double *dimension){
    // this->clusterId = id;
    this->clusterCoordinates = new Vector(id, size);
    this->clusterCoordinates->initVector(dimension);

}

void Cluster::printClusterInfo(void) {
    cout << endl << "Cluster Info:" << endl;
    this->clusterCoordinates->printVector();
}