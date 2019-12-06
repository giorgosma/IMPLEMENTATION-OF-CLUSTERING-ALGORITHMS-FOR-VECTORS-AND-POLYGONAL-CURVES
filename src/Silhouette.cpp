#include "../lib/Silhouette.h"

Silhouette::Silhouette(Initialization *init, bool isCurve, bool complete) {
    cout << "Silhouette is being created" << endl;
    ofstream total;
    total.open("Out/outputFile.txt", ofstream::out | ofstream::app);

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
    for (int i = 0; i < init->getClusterSize(); i++) {                      // for each Cluster
        Cluster * cluster = init->getClusterItem(i);
        this->clusterItems = cluster->getItems();
        // cout << "CLUSTER-" << i + 1 << " { size: " << (int)(this->clusterItems->size()) << ", " << cluster->getCentroid()->getVectorID() << " }" << endl;   
        total << "CLUSTER-" << i + 1 << " { size: " << (int)(this->clusterItems->size()) << ", " << cluster->getCentroid()->getVectorID() << " }" << endl;  
        for (int j = 0; j < (int)(this->clusterItems->size()); j++) {       // for each Cluster's Item
            double alpha = this->computeAlpha(this->clusterItems->at(j));
            double beta = this->computeBeta(init, this->clusterItems->at(j), cluster->getCentroid());
            this->clusterItems = cluster->getItems();

            sigma[i].push_back((beta - alpha) / max(alpha, beta));          // compute Cluster's Item S(I)
            avgSigma[i] += sigma[i].back();
        }
        sumAvg += avgSigma[i];
        avgSigma[i] = avgSigma[i] / (int)(this->clusterItems->size());      // AVG Cluster's S(P)
    }
    int datasetSize = 0;
    for (int i = 0; i < init->getClusterSize(); i++) {
        datasetSize += (int)(init->getClusterItem(i)->getItems()->size());
    }
    sumAvg = sumAvg / datasetSize;                                          // STOTAL
    // cout << "Silhouette: [ ";
    total << "Silhouette: [ ";
    for (int i = 0; i < init->getClusterSize(); i++) {
        // cout << avgSigma[i] << " ";
        total << avgSigma[i] << " ";
        // if (i < init->getClusterSize() - 1)
            // cout << ", ";
            total << ", ";
    }
    total << sumAvg << " ]" << endl;
    // cout << " ]" << endl << endl << sumAvg << endl << endl;
    cout << endl << endl << sumAvg << endl << endl;

    if (complete) {                                                         // write all Items to output file
        for (int i = 0; i < init->getClusterSize(); i++) {
            Cluster * cluster = init->getClusterItem(i);
            this->clusterItems = cluster->getItems();
            // cout << "CLUSTER-" << i + 1 << " { ";  
            total << "CLUSTER-" << i + 1 << " { "; 
            for (int j = 0; j < (int)(this->clusterItems->size()); j++) {  
                // cout << this->clusterItems->at(j)->getVectorID();
                total << this->clusterItems->at(j)->getVectorID();
                if (j < (int)(this->clusterItems->size()) - 1)
                    // cout << ", ";
                    total << ", ";
            }
            // cout << " }" << endl;
            total << " }" << endl;
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
    for (int i = 0; i < clusterSize; i++) {                 // for each cluster's Item
        alpha += this->distance->calculateDistance(vector, this->clusterItems->at(i)); 
    }
    return (alpha / clusterSize);
    
}

double Silhouette::computeBeta(Initialization *init, Vector *vector, Vector *centroid) {
    int indexSecondCluster = -1;
    double secondDist = 0.0;
    for (int i = 0; i < init->getClusterSize(); i++) {                          // for each Cluster
        Cluster * cluster = init->getClusterItem(i);
        if (cluster->getCentroid()->getVectorID() == centroid->getVectorID())   // if Best Cluster continue
            continue;
        double newDist = distance->calculateDistance(vector, cluster->getCentroid());
        if (indexSecondCluster == -1 || secondDist > newDist) {                 // Compute Second Cluster
            secondDist = newDist;
            indexSecondCluster = i;  
        }
    }
    this->clusterItems = init->getClusterItem(indexSecondCluster)->getItems();  // Compute beta as alfa with Second Cluster's Items
    return this->computeAlpha(vector);
}
