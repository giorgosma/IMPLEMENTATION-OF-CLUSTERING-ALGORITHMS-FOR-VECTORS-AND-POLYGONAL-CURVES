#include "../lib/RandomSelection.h"

RandomSelection::RandomSelection(int K, VectorArray *vectorArray) : Initialization(K) {
    cout << "RandomSelection is being created" << endl;
    for (int i = 0; i < this->getClusterSize(); i++) {
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        default_random_engine generator (seed);
        uniform_int_distribution<int> distribution(0, vectorArray->getVectorArraySize());
        Vector * centroid = vectorArray->getVectorArrayItem(distribution(generator));
        distribution.reset();
    
        Cluster * clusterItem = this->getClusterItem(i);
        clusterItem->initCluster(centroid->getVectorID(), centroid->getVectorDimension(), centroid->getVectorCoordinates());

        clusterItem->printClusterInfo();
    }
}

RandomSelection::~RandomSelection(void) {
    cout << "RandomSelection is being deleted" << endl;
}

// void RandomSelection::getClusterSize(void) {
//     cout << "RandomSelection ClusterSize "  << endl;
//     Initialization::getClusterSize();
// }
