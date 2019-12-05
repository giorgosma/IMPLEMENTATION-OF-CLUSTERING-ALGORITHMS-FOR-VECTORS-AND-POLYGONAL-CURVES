#include "../lib/LSH.h"

#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;

LSH::LSH(int L, int TableSize, int w, int dimensionSize, int k) {
    this->L = L;
    this->LhashTables = new vector<HashTable *>[L];
    for (int i = 0; i < L; i++) {
        (this->LhashTables[i]).push_back(new HashTable(TableSize, w, dimensionSize, k));
    }
    cout << "LSH is being created" << endl;
}

LSH::~LSH(void) {
    for (int i = 0; i < L; i++) {
        delete this->LhashTables[i].at(0);
    }
    delete [] this->LhashTables;
    cout << "LSH is being deleted" << endl;
}

void LSH::printLSH(void) {
    for (int i = 0; i < this->L; i++) {
        cout << "HT " << i << " " << &((this->LhashTables[i]).at(0)) << endl;
        this->LhashTables[i].at(0)->print();
    }
}

void LSH::addItem(Vector *vector) {
    //unsigned int g;
    for (int i = 0; i < this->L; i++) {
        (this->LhashTables[i]).at(0)->storeVector(vector, i);
    }
}

void LSH::addG(Vector * vector){
    for(int i = 0; i < this->L; i++ ){
        ((this->LhashTables[i]).at(0))->addG(vector);
    }
}

int locmodulo(int x, int y){
    if(x >= 0)
        return x % y;
    else
        return x % y + y;
}

Vector * LSH::getNN(Vector * vec){
    
    ofstream total;
    total.open("exactLSHPoints.txt", ofstream::out | ofstream::app);
    // ofstream outfile;
    // outfile.open("LSHoutputFile.txt", ofstream::out | ofstream::app);

    Vector * nn = NULL;
    int min = 2147483647;

    vector <Vector *> * bucket;
    // cout << "Query: " << vec->getVectorID() << endl;
    // outfile << "Query: " << vec->getVectorID() << endl;
    total << "Query: " << vec->getVectorID() << endl;


    auto start = high_resolution_clock::now(); 
    for(int i=0; i<this->L; i++) {
        bucket = (this->LhashTables[i]).at(0)->getBucket(locmodulo(vec->getG(i), (this->LhashTables[i]).at(0)->getTableSize()));
        //int countComparisons = 0;
        for(int j=0; j<(int) bucket->size(); j++) {
            // if (countComparisons > 100*(this->L))
            //     break;
            Manhattan *manhattanDistance = new Manhattan(vec, bucket->at(j));
            int dist = manhattanDistance->getManhattan();
            delete manhattanDistance;
            if(dist < min){
                min = dist;
                nn = bucket->at(j);
            }
            //countComparisons++;
        }
    }
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);

    if(nn == NULL){
        // cout << "\tLSH NN     : -" << endl;
        // cout << "\tLSH Dist   : -" << endl;
        // cout << "\tLSH Time   : " << totalTime << endl;
        // outfile << "\tLSH NN     : -" << endl;
        // outfile << "\tLSH Dist   : -" << endl;
        // outfile << "\tLSH Time   : " << totalTime << endl;
        total << "\tLSH NN     : -" << endl;
        total << "\tLSH Dist   : -" << endl;
        total << "\tLSH Time   : " << duration.count() << endl;
    }
    else{
        // cout << "\tLSH NN     : " << nn->getVectorID() << endl;
        // cout << "\tLSH Dist   : " << min << endl;
        // cout << "\tLSH Time   : " << totalTime << endl;
        // outfile << "\tLSH NN     : " << nn->getVectorID() << endl;
        // outfile << "\tLSH Dist   : " << min << endl;
        // outfile << "\tLSH Time   : " << totalTime << endl;
        total << "\tLSH NN     : " << nn->getVectorID() << endl;
        total << "\tLSH Dist   : " << min << endl;
        total << "\tLSH Time   : " << duration.count() << endl;
    }
    // outfile.close();
    total.close();
    return nn;
}

vector <Vector *> LSH::getNNBonus(Vector * vec, int r){
    vector <Vector *> nn;

    vector <Vector *> * bucket;
    //vec->printVector();
    ofstream outfile;
    outfile.open("LSHPointsBonus.txt", ofstream::out | ofstream::app);

    //cout << "Query: " << query->getVectorID() << endl;
    outfile << "Query: " << vec->getVectorID() << endl;

    //cout << "g is " << vec->getG(0) << endl;

    for(int i=0; i<this->L; i++){
        bucket = (this->LhashTables[i]).at(0)->getBucket(locmodulo(vec->getG(i), (this->LhashTables[i]).at(0)->getTableSize()));
        for(int j=0; j<(int) bucket->size(); j++){
            Manhattan *manhattanDistance = new Manhattan(vec, bucket->at(j));
            int dist = manhattanDistance->getManhattan();
            if(dist < r){
                nn.push_back(bucket->at(j));
            }
        }
    }
    if(nn.size() == 0){
        // cout << "No NN found" << endl;
        outfile << "\tHyperCube nn     : -" << endl;
    }
    else{
        // cout << "Found " << nn.size()  << " neighbors within a radius of " << r << endl;
        for (int i = 0; i < (int)(nn.size()); i++) {
            outfile << "\tHyperCube NN     : " << nn[i]->getVectorID() << endl;
        }
    }
    
    return nn;
}

vector<string> LSH::getBucketVectorsID(Vector * vec) {
    vector<string> bucketIDs;
    vector <Vector *> * bucket;
    for(int i=0; i<this->L; i++) {
        bucket = (this->LhashTables[i]).at(0)->getBucket(locmodulo(vec->getG(i), (this->LhashTables[i]).at(0)->getTableSize()));
        for(int j=0; j<(int) bucket->size(); j++) {
            bucketIDs.push_back(bucket->at(j)->getVectorID());
        }
    }
    return bucketIDs;
}

int LSH::getIndex(int G) {
    return locmodulo(G, (this->LhashTables[0]).at(0)->getTableSize());
}

int LSH::getL() {
    return this->L;
}