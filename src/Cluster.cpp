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
    cout << endl << "Cluster Info:" << endl;
    this->centroid->printVector();
}

Vector * Cluster::getCentroid(void){
    return this->centroid;
}