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

    this->grid = new Grids(L_grids, 0.01, 2);
    this->lshSize = L_grids;
    vector<vector<vector<double> *> *> * LGrids = grid->projectToGrids(veCurves);
    // this->vectorArraySize = static_cast<int>(LGrids->size());
    // cout << "veCurves->size() " << veCurves->at(0)->size() <<endl;
    this->vectorArraySize = L_grids;
    cout << "SIZE " << this->vectorArraySize << endl;
    VectorArray **vectorArray = new VectorArray*[this->vectorArraySize];
    // cout << "LGrids->size() " << LGrids->size() <<endl; 
    this->lsh = new LSH*[LGrids->size()];
    for (int i = 0; i < (int)(LGrids->size()); i++) {
        // cout << "LGrids->at(i)->size() " << LGrids->at(i)->size() << endl;
        vectorArray[i] = new VectorArray(LGrids->at(i)->size());
        // cout << "Dimension " << (int)(LGrids->at(i)->at(0)->size()) << endl;
        this->lsh[i] = new LSH(1, (LGrids->at(i)->size())/8, 4000, (int)(LGrids->at(i)->at(0)->size()), k);
        for (int j = 0; j < (int)(LGrids->at(i)->size()); j++) {
            Vector *vector = new Vector(to_string(j), LGrids->at(i)->at(j)->size());
            double *dimension = new double[LGrids->at(i)->at(j)->size()];
            for (int l = 0; l < (int)(LGrids->at(i)->at(j)->size()); l++) {
                dimension[l] = LGrids->at(i)->at(j)->at(l);
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

}

RangeSearch::~RangeSearch(void) {
    cout << "RangeSearch is being deleted" << endl;
    if (this->isCurve) {
        for (int i = 0; i < this->vectorArraySize; i++) {
            delete this->vectorArray[i];
        }
        delete[] this->vectorArray;
        delete this->grid;
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
    //
        if (this->isCurve) {
            this->setupCurvesAssignment(init, vectors);
            return;
        }
    //
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
    for (int i = 0; i < this->lshSize; i++) {                       // for each LSH
        vector<Vector *> LloydsVectorArray;
        for (int j = 0; j < vectors->getVectorArraySize(); j++) {   // for each Vector
            set<Cluster *> umapClusters;
            Vector *vector = vectors->getVectorArrayItem(j);
            // if (j < 20)
                // cout << vector->getVectorID() << endl << " G: ";
            gArray = vector->getG();
            for (int k = 0; k < (int)(gArray->size()); k++) {       // for each Vector's G
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
                else {                                              // indexG was found in 
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
        }
        this->setupAssignment(init, LloydsVectorArray);
    }
    for (int i = 0; i < init->getClusterSize(); i++) {
        init->getClusterItem(i)->printClusterInfo();
    }
    delete[] umap;
}

Cluster * RangeSearch::getRealCluster(Initialization * init, Vector *gridCentroid) {
    for (int i = 0; i < init->getClusterSize(); i++) {
        Cluster * cluster = init->getClusterItem(i);
        if (cluster->getCentroid()->getVectorID() == gridCentroid->getVectorID())
            return cluster;
    }
    return NULL;
}

void RangeSearch::setupCurvesAssignment(Initialization * init, VectorArray * vectors) {
    int umapSize = 0;
    for (int i = 0; i < this->lshSize; i++)
        umapSize += this->lsh[i]->getL();
    struct arrayMap * umap = new struct arrayMap[umapSize];      // INDEX_BUCKET, CLSUTER_CENTROID
    vector<unsigned int> *gArray;

    vector<vector<double> *> * centroidGrids = new vector<vector<double> *>;    // Convert centroids to GRIDS
    for (int j = 0; j < init->getClusterSize(); j++) {
        Vector *centroid = init->getClusterItem(j)->getCentroid();
        cout << centroid->getVectorID() << endl;
        double * pArray = centroid->getVectorCoordinates();    
        vector<double> * centroidVector = new vector<double>(pArray, pArray + (sizeof(double) * (centroid->getVectorDimension()) / sizeof(pArray[0])));
        centroidGrids->push_back(centroidVector);    
    }
    vector<vector<vector<double> *> *> * LGridsCentroids = this->grid->projectToGrids(centroidGrids);
    int vectorArraySize = static_cast<int>(LGridsCentroids->size());
    VectorArray **vectorArray = new VectorArray*[LGridsCentroids->size()];
    for (int i = 0; i < this->lshSize; i++) {
        vectorArray[i] = new VectorArray((int)(LGridsCentroids->at(i)->size()));
        // for (int j = 0; j < (int)(LGridsCentroids->at(i)->size()); j++) {
        cout << "vectorArray [ " << i << " ] Size " << vectorArray[i]->getVectorArraySize() << endl;
        for (int j = 0; j < vectorArray[i]->getVectorArraySize(); j++) {
            Vector *vector = new Vector(to_string(j), max(this->vectorArray[i]->getVectorArrayItem(0)->getSize() , (int)(LGridsCentroids->at(i)->at(j)->size())));
            double *dimension = new double[max(this->vectorArray[i]->getVectorArrayItem(0)->getSize() , (int)(LGridsCentroids->at(i)->at(j)->size()))];
            for (int l = 0; l < max(this->vectorArray[i]->getVectorArrayItem(0)->getSize() , (int)(LGridsCentroids->at(i)->at(j)->size())); l++) {
                if (l >= (int)(LGridsCentroids->at(i)->at(j)->size()))
                    dimension[l] = 0;
                else
                    dimension[l] = LGridsCentroids->at(i)->at(j)->at(l);
            }
            vector->initVector(dimension);
            delete[] dimension;
            vectorArray[i]->addVectorToArray(vector, j);
            // this->lsh[i]->addItem(vectorArray[i]->getVectorArrayItem(j));
            // (this->lsh[i])->addG(vectorArray[i]->getVectorArrayItem(j)); 
            cout << "Centroid Dimension " << vector->getSize() << " Other Dimension " << this->vectorArray[i]->getVectorArrayItem(0)->getSize() << " " << this->vectorArray[i]->getVectorArrayItem(3)->getSize()<< endl;
            ((this->lsh)[i])->addG(vector); 
            delete LGridsCentroids->at(i)->at(j);
        }
        delete LGridsCentroids->at(i);
    }
    delete LGridsCentroids; 

    for (int i = 0; i < this->lshSize; i++) {
        for (int j = 0; j < init->getClusterSize(); j++) {
            Vector *centroid = vectorArray[i]->getVectorArrayItem(j);
    //         // vector<vector<double> *> * veCurves
    //         // vector<vector<vector<double> *> *> * LGrids = grid->projectToGrids(veCurves);
    //         // (this->lsh[i])->addG(centroid);     // create G for Centroids
    //         // cout << "-" << centroid->getVectorID() << endl;
    //         // if (i < this->lshSize - 1)
    //         //     continue;
            gArray = centroid->getG();
            for (int k = 0; k < (int)(gArray->size()); k++) {  // fill umap with key G and centroids
                // umap[k].umap[this->lsh[i]->getIndex(gArray->at(k))].push_back(init->getClusterItem(j));
                umap[i].umap[this->lsh[i]->getIndex(gArray->at(k))].push_back(init->getClusterItem(j));
            //     // cout << "\t" << this->lsh[i]->getIndex(gArray->at(k)) << endl;
            }
        }
    }

    // int xIndex;
    // for (int i = 0; i < umapSize; i++) {
    //     cout << "- HT " << i << endl;
    //     for (auto x : umap[i].umap) {
    //         cout << "\t" << x.first << endl;
    //         xIndex = x.first;
    //         cout << "\t " << xIndex << " SIZE " << (((umap[i]).umap)[xIndex]).size() << endl;
    //         for (int j = 0; j < (int)(x.second).size(); j++) {
    //             cout << "\t\t S " << (x.second[j])->getCentroid()->getVectorID() << endl;
    //             // cout << "\t\t I " << ((((umap[i]).umap)[xIndex])[j])->getCentroid()->getVectorID() << endl;
    //         }
    //     } 
    // }

    Cluster * MinCluster = NULL;
    vector<Vector *> LloydsVectorArray;
    for (int j = 0; j < (this->vectorArray[0])->getVectorArraySize(); j++) {    // For each Vector
        set<Cluster *> umapClusters;
        string id = vectors->getVectorArrayItem(j)->getVectorID();
        for (int i = 0; i < this->lshSize; i++) {                               // For each Vector's Grid-Vector
            Vector *vector = (this->vectorArray[i])->getVectorArrayItem(j);
            if (id != (this->vectorArray[i])->getVectorArrayItem(j)->getVectorID())
                cout << "------------------PROBLEM!!!!" << id << " and " << (this->vectorArray[i])->getVectorArrayItem(j)->getVectorID() << endl;
            gArray = vector->getG();                                            // get G
            for (int k = 0; k < (int)(gArray->size()); k++) {
                int indexG = this->lsh[i]->getIndex(gArray->at(k));
                if (((umap[i]).umap).find(indexG) == ((umap[i]).umap).end()) {
                }
                else {                                              // indexG was found in 
                    for (int l = 0; l < (int)(((umap[i]).umap)[indexG]).size(); l++) {  
                        Cluster *realCluster = this->getRealCluster(init, ((((umap[i]).umap)[indexG])[l])->getCentroid());
                        if (realCluster == NULL)
                            cout << "--REAL PROBLEM HERE" << endl;
                        else 
                            umapClusters.insert(realCluster);
                    }
                }
            }
        }
        if (umapClusters.size() == 0) {
            cout << "Lloyds for " << vectors->getVectorArrayItem(j)->getVectorID() << endl;
            LloydsVectorArray.push_back(vectors->getVectorArrayItem(j));
        }
        else {
            MinCluster = this->getMinCluster(umapClusters, vectors->getVectorArrayItem(j));
            MinCluster->addItemToCluster(vectors->getVectorArrayItem(j));
            cout << vectors->getVectorArrayItem(j)->getVectorID() << " TO CENTROID " << MinCluster->getCentroid()->getVectorID() << endl;
        }
    }
    this->setupAssignment(init, LloydsVectorArray);

    for (int i = 0; i < init->getClusterSize(); i++) {
        init->getClusterItem(i)->printClusterInfo();
    }

    for (int i = 0; i < vectorArraySize; i++) {
        delete vectorArray[i];
    }
    delete[] vectorArray;
    for (int i = 0; i < (int)(centroidGrids->size()); i++){
        delete centroidGrids->at(i);
    }
    delete centroidGrids;
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
    Distance * distance;
    if (this->isCurve)
        distance = new DTW();
    else 
        distance = new Manhattan();

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
        }
                                                                 // store item to the minDist centroid - cluster
        init->getClusterItem(indexCluster)->addItemToCluster(vectors[i]);
        cout << "Added " << vectors[i]->getVectorID() << endl;
        initCounter++;
        // if (i > 10)
        //     break;
    }
    // cout << "Inited " << initCounter << " Vectors" << endl;
    delete distance;
}