#include "../lib/Silhouette.h"

Silhouette::Silhouette(Initialization *init, bool isCurve, bool complete) {
    cout << "Silhouette is being created" << endl;
    double *avgSigma = new double[init->getClusterSize()]();
    double sumAvg = 0;
    // for (int i = 0; i < init->getClusterSize(); i++)
    //     cout << avgSigma[i] << " ";
    cout << endl;
    this->isCurve = isCurve;
    if (this->isCurve)
        this->distance = new DTW();
    else
        this->distance = new Manhattan();
    this->sigma = new vector<double>[init->getClusterSize()];
    for (int i = 0; i < init->getClusterSize(); i++) {
        Cluster * cluster = init->getClusterItem(i);
        this->clusterItems = cluster->getItems();
        cout << "CLUSTER-" << i + 1 << " { size: " << (int)(this->clusterItems->size()) << ", " << cluster->getCentroid()->getVectorID() << " }" << endl;  
        for (int j = 0; j < (int)(this->clusterItems->size()); j++) {
            double alpha = this->computeAlpha(this->clusterItems->at(j));
            double beta = this->computeBeta(init, this->clusterItems->at(j), cluster->getCentroid());
            this->clusterItems = cluster->getItems();

            sigma[i].push_back((beta - alpha) / max(alpha, beta));
            avgSigma[i] += sigma[i].back();
        }
        sumAvg += avgSigma[i];
        avgSigma[i] = avgSigma[i] / (int)(this->clusterItems->size());
    }
    int datasetSize = 0;
    for (int i = 0; i < init->getClusterSize(); i++) {
        datasetSize += (int)(init->getClusterItem(i)->getItems()->size());
    }
    sumAvg = sumAvg / datasetSize;
    cout << "Silhouette: [ ";
    for (int i = 0; i < init->getClusterSize(); i++) {
        cout << avgSigma[i] << " ";
        if (i < init->getClusterSize() - 1)
            cout << ", ";
    }
    cout << " ]" << endl << endl << sumAvg << endl << endl;

    if (complete) {
        for (int i = 0; i < init->getClusterSize(); i++) {
            Cluster * cluster = init->getClusterItem(i);
            this->clusterItems = cluster->getItems();
            cout << "CLUSTER-" << i + 1 << " { ";  
            for (int j = 0; j < (int)(this->clusterItems->size()); j++) {  
                cout << this->clusterItems->at(j)->getVectorID();
                if (j < (int)(this->clusterItems->size()))
                    cout << ", ";
            }
            cout << " }" << endl;
        }
    }


    delete[] avgSigma;
}

Silhouette::~Silhouette(void) {
    delete[] this->sigma;
    delete this->distance;
    cout << "Silhouette is being deleted" << endl;
}

double Silhouette::computeAlpha(Vector *vector) {
    double alpha = 0.0;
    int clusterSize = (int)(this->clusterItems->size());
    for (int i = 0; i < clusterSize; i++) {
        alpha += this->distance->calculateDistance(vector, this->clusterItems->at(i)); 
    }
    return (alpha / clusterSize);
    
}

double Silhouette::computeBeta(Initialization *init, Vector *vector, Vector *centroid) {
    int indexSecondCluster = -1;
    double secondDist = 0.0;
    for (int i = 0; i < init->getClusterSize(); i++) {
        Cluster * cluster = init->getClusterItem(i);
        if (cluster->getCentroid()->getVectorID() == centroid->getVectorID())
            continue;
        double newDist = distance->calculateDistance(vector, cluster->getCentroid());
        if (indexSecondCluster == -1 || secondDist > newDist) {
            secondDist = newDist;
            indexSecondCluster = i;  
        }
    }
    this->clusterItems = init->getClusterItem(indexSecondCluster)->getItems();
    return this->computeAlpha(vector);
}
