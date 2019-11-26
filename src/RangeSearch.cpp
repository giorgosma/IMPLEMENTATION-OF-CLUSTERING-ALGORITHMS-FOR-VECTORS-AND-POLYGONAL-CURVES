#include "../lib/RangeSearch.h"

RangeSearch::RangeSearch(int L, int TableSize, int W, int dimensionSize, int k, VectorArray *vectors) : Assignment() {
    cout << "RangeSearch is being created" << endl;
    this->lsh = new LSH*[1];
    this->lsh[0] = new LSH(L, TableSize, W, dimensionSize, k);  
    this->isCurve = false;

    int counter = 0;
    for (int i = 0; i < vectors->getVectorArraySize(); i++) {
        this->lsh[0]->addItem(vectors->getVectorArrayItem(i));
        counter++;
        if (counter == 100) {
            cout << "ADDED " << i + 1 << " Vectors"<< endl;
            counter = 0;
        }
        if (i == vectors->getVectorArraySize() - 1)
            cout << "ADDED " << i + 1 << " Vectors"<< endl;
    }

    this->lshSize = 1;
}

RangeSearch::RangeSearch(int k, int L_grids, VectorArray *curves, vector<vector<double> *> * veCurves) : Assignment() {
    cout << "RangeSearch is being created" << endl;
    this->isCurve = true;

    Grids * grid = new Grids(L_grids, 0.01, 2);
    this->lshSize = L_grids;
    vector<vector<vector<double> *> *> * LGrids = grid->projectToGrids(veCurves);
    this->vectorArraySize = static_cast<int>(LGrids->size());
    VectorArray **vectorArray = new VectorArray*[LGrids->size()];
    this->lsh = new LSH*[LGrids->size()];
    for (int i = 0; i < (int)(LGrids->size()); i++) {
        vectorArray[i] = new VectorArray(LGrids->at(i)->size());
        this->lsh[i] = new LSH(1, (LGrids->at(i)->size())/8, 4000, LGrids->at(i)->at(0)->size(), k);
        for (int j = 0; j < (int)(LGrids->at(i)->size()); j++) {
            Vector *vector = new Vector(to_string(j), LGrids->at(i)->at(j)->size());
            double *dimension = new double[LGrids->at(i)->at(j)->size()];
            for (int k = 0; k < (int)(LGrids->at(i)->at(j)->size()); k++) {
                dimension[k] = LGrids->at(i)->at(j)->at(k);
            }
            vector->initVector(dimension);
            delete[] dimension;
            vectorArray[i]->addVectorToArray(vector, j);
            this->lsh[i]->addItem(vectorArray[i]->getVectorArrayItem(j));
            delete LGrids->at(i)->at(j);
        }
        delete LGrids->at(i);
    }
    this->vectorArray = vectorArray;
    // for (int i = 0; i < (int)(LGrids->size()); i++) {
    //     delete vectorArray[i];
    // }
    // delete[] vectorArray; 
    delete LGrids; 
    delete grid; 

}

RangeSearch::~RangeSearch(void) {
    cout << "RangeSearch is being deleted" << endl;
    if (this->isCurve) {
        for (int i = 0; i < this->vectorArraySize; i++) {
            delete this->vectorArray[i];
        }
        delete[] this->vectorArray;
    } 
    for (int i = 0; i < this->lshSize; i++) {
        delete this->lsh[i];
    }
    delete[] this->lsh;
}

void RangeSearch::initLSH(VectorArray * vectors) {
    for (int i = 0; i < vectors->getVectorArraySize(); i++) {
        this->lsh[0]->addItem(vectors->getVectorArrayItem(i));
    }
}

// int locmodulo(int x, int y){
//     if(x >= 0)
//         return x % y;
//     else
//         return x % y + y;
// }

void RangeSearch::setupAssignment(Initialization * init, VectorArray * vectors) {
    int umapSize = 0;
    for (int i = 0; i < this->lshSize; i++)
        umapSize += this->lsh[i]->getL();
    struct arrayMap * umap = new struct arrayMap[umapSize];      // INDEX_BUCKET, CLSUTER_CENTROID
    vector<unsigned int> *gArray;

    for (int i = 0; i < this->lshSize; i++) {
        for (int j = 0; j < init->getClusterSize(); j++) {
            Vector *centroid = init->getClusterItem(j)->getCentroid();
            this->lsh[i]->addG(centroid);     // create G for Centroids
            // cout << "-" << centroid->getVectorID() << endl;
            gArray = centroid->getG();
            for (int k = 0; k < (int)(gArray->size()); k++) {  // fill umap with key G and centroids
                umap[k].umap[this->lsh[i]->getIndex(gArray->at(k))].push_back(init->getClusterItem(j));
                // umap[this->lsh[i]->getIndex(gArray->at(k))].push_back(init->getClusterItem(j));
                // cout << "\t" << this->lsh[i]->getIndex(gArray->at(k)) << endl;
            }
        }
    } 

    //
    int xIndex;
    for (int i = 0; i < umapSize; i++) {
        cout << "- HT " << i << endl;
        for (auto x : umap[i].umap) {
            cout << "\t" << x.first << endl;
            xIndex = x.first;
            cout << "\t " << xIndex << " SIZE " << (((umap[i]).umap)[xIndex]).size() << endl;
            for (int j = 0; j < (int)(x.second).size(); j++) {
                cout << "\t\t S " << (x.second[j])->getCentroid()->getVectorID() << endl;
                // cout << "\t\t I " << ((((umap[i]).umap)[xIndex])[j])->getCentroid()->getVectorID() << endl;
            }
        } 
    }
// return;
    // for (auto x : umap) {
    //     cout << x.first << " -->" << x.second.size() << endl; 
    //     for (int i = 0; i < x.second.size(); i++)
    //         cout << "   " << x.second[i]->getCentroid()->getVectorID() << endl; 
    // }
    // unordered_map<int, vector<Cluster *>>::iterator itr; 
    // for (itr = umap.begin(); itr != umap.end(); ++itr) { 
    //     cout << itr->first << endl;
    //     for (int i = 0; i < (int)((itr->second).size()); i++)
    //         cout << "\t" << (itr->second)[i]->getCentroid()->getVectorID() << endl;
    // } 
    // return;
    //

    Cluster * MinCluster = NULL;
    for (int i = 0; i < this->lshSize; i++) {
        vector<Vector *> LloydsVectorArray;
        for (int j = 0; j < vectors->getVectorArraySize(); j++) {
            set<Cluster *> umapClusters;
            Vector *vector = vectors->getVectorArrayItem(j);
            // if (j < 20)
                // cout << vector->getVectorID() << endl << " G: ";
            gArray = vector->getG();
            for (int k = 0; k < (int)(gArray->size()); k++) {
                int indexG = this->lsh[i]->getIndex(gArray->at(k));
                // if (j < 20)
                    // cout << indexG << " ";
                if (((umap[k]).umap).find(indexG) == ((umap[k]).umap).end()) {
                    // unordered_map<int, vector <Cluster *>>::iterator it = (umap[k]).umap;
                    // for (int l = 0; l < (int)(((umap[k]).umap)[indexG]).size(); l++) {
                    //     umapClusters.insert((((umap[k]).umap)[indexG])[l]);
                    //     cout << "INSERTED umapClusters " << (((umap[k]).umap)[indexG])[l]->getCentroid()->getVectorID() << endl;
                    // }
                    // cout << "UMAP " << k << " INDEX " << indexG << " SIZE " << (int)((umap[k]).umap[indexG]).size() << endl;
                }
                else {
                    for (int l = 0; l < (int)(((umap[k]).umap)[indexG]).size(); l++) {
                        umapClusters.insert((((umap[k]).umap)[indexG])[l]);
                        // cout << "INSERTED umapClusters " << (((umap[k]).umap)[indexG])[l]->getCentroid()->getVectorID() << endl;
                    }
                }
            }
            if (j < vectors->getVectorArraySize()) {
                // cout << endl;
                // if ((int)(umapClusters).size() > 0)
                //     cout << "   UMAP SIZE " << (int)(umapClusters).size() << endl;
                // for (int k = 0; k < (int)(umapClusters.size()); k++) {
                //     set<Cluster *>::iterator it = umapClusters.begin();
	            //     advance(it, k);
  	            //     cout << "\t\t" << (*it)->getCentroid()->getVectorID() << endl;
                // } 
                if (umapClusters.size() == 0) {
                    cout << "Lloyds for " << vector->getVectorID() << endl;
                    LloydsVectorArray.push_back(vector);
                }
                else {
                    MinCluster = this->getMinCluster(umapClusters, vector);
                    MinCluster->addItemToCluster(vector);
                    cout << vector->getVectorID() << " TO CENTROID " << MinCluster->getCentroid()->getVectorID() << endl;
                }
            }
    //         if (clustersVectorArray.size() > 1) {
    //             Distance * distance = new Manhattan();
    //             cout << clustersVectorArray[0] << " -> " << (umap.at(clustersVectorArray[0])[0])->getCentroid()->getVectorID() << endl;
    //             double minDist = distance->calculateDistance(vector, (umap.at(clustersVectorArray[0])[0])->getCentroid() );
    //             Cluster * vectorCluster = umap.at(clustersVectorArray[0])[0];
    //             for (int k = 1; k < (int)(clustersVectorArray.size()); k++) {
    //                 double newDist;
    //                 if (umap.at(clustersVectorArray[k]).size() > 1) {
    //                     for (int l = 1; l < (int)(umap.at(clustersVectorArray[k]).size()); l++) {
    //                         newDist = distance->calculateDistance(vector, (umap.at(clustersVectorArray[k])[l])->getCentroid());
    //                         if (minDist > newDist){
    //                             minDist = newDist;
    //                             vectorCluster = umap.at(clustersVectorArray[k])[l];  
    //                         }
    //                     }
    //                 }
    //                 else {
    //                     newDist = distance->calculateDistance(vector, (umap.at(clustersVectorArray[k])[0])->getCentroid());
    //                     if (minDist > newDist){
    //                         minDist = newDist;
    //                         vectorCluster = umap.at(clustersVectorArray[k])[0];    
    //                     }
    //                 }
    //             }
    //             vectorCluster->addItemToCluster(vector);
    //         }
    //         else if (clustersVectorArray.size() == 1) { // push vector to clustersVectorArray[0]
    //             cout << clustersVectorArray[0] << " -> " << (umap.at(clustersVectorArray[0])[0])->getCentroid()->getVectorID() << endl;
    //             (umap.at(clustersVectorArray[0])[0])->addItemToCluster(vector);
    //         }
    //         else{}
                // get minDist from all clusters -> call Lloyds
                // store to a Varray and in the end call Lloyds
        }
        this->setupAssignment(init, LloydsVectorArray);
    }
    for (int i = 0; i < init->getClusterSize(); i++) {
        init->getClusterItem(i)->printClusterInfo();
    }
    delete[] umap;
}

Cluster * RangeSearch::getMinCluster(set<Cluster *> setOfClusters, Vector * vector) {
    set<Cluster *>::iterator it = setOfClusters.begin();
	advance(it, 0);
    Cluster *minCluster = (*it);
    if (setOfClusters.size() > 1) {
        Distance * dist;
        if (this->isCurve) {
            dist = new DTW();
        }
        else {
            dist = new Manhattan();
        }

        double minDist = dist->calculateDistance((*it)->getCentroid(), vector);
        for (int i = 1; i < (int)setOfClusters.size(); i++) {
            it = setOfClusters.begin();
            advance(it, i);
            double newDist = dist->calculateDistance((*it)->getCentroid(), vector);
            if (newDist < minDist) {
                minDist = newDist;
                minCluster = (*it);
            }
        }
        delete dist;
    }
    return minCluster;
}

void RangeSearch::setupAssignment(Initialization * init, vector<Vector *> vectors) {
    Distance * distance = new Manhattan();
    int initCounter = 0;
    cout << "VectorArray = " << vectors.size() << " ClusterSize " << init->getClusterSize() << endl;
    for (int i = 0; i < (int)vectors.size(); i++) {       // for each vector item
        // if (this->isCentroid(vectors->getVectorArrayItem(i), init)){
        //     // cout << "Vector " << vectors->getVectorArrayItem(i)->getVectorID() << endl;
        //     continue;
        // }
        double minDist = distance->calculateDistance(vectors[i], init->getClusterItem(0)->getCentroid());
        int indexCluster = 0;
        for (int j = 1; j < init->getClusterSize(); j++) {          // for each centroid - cluster
            double newDist = distance->calculateDistance(vectors[i], (init->getClusterItem(j))->getCentroid());
            if (minDist > newDist){
                minDist = newDist;
                indexCluster = j;  
            }
        }                                                         // store item to the minDist centroid - cluster
        init->getClusterItem(indexCluster)->addItemToCluster(vectors[i]);
        initCounter++;
    }
    // cout << "Inited " << initCounter << " Vectors" << endl;
    delete distance;
}