#include "../lib/ExactNN.h"

#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;

ExactNN::ExactNN(VectorArray *vectorArray, int rayDistance) : pVectorArray(vectorArray), rayDistance(rayDistance) {
    // cout << "ExactNN is being created" << endl;
}

ExactNN::~ExactNN(void) {
    // cout << "ExactNN is being deleted" << endl;
    for (int i = 0; i < (int)(this->neighborsArray.size()); i++)
        delete this->neighborsArray[i].manhattanDistance;
}

void ExactNN::testVector(Vector *vector, Manhattan *manhattanDistance) {
    this->neighborsArray.push_back(NeighborsArray());
    this->neighborsArray[this->neighborsArray.size() - 1].vector = vector;
    this->neighborsArray[this->neighborsArray.size() - 1].manhattanDistance = manhattanDistance;
}

void ExactNN::printNN(void) {
    for (int i = 0; i < (int)(this->neighborsArray.size()); i++) {
        cout << "neighborsArray [" << i << "]" << endl << "\t" << (this->neighborsArray[i]).manhattanDistance->getManhattan() << endl << "\t";
        ((this->neighborsArray[i]).vector)->printVector();
    }

}

void ExactNN::addNeighbor(Vector *vector, Manhattan *manhattanDistance) {
    this->neighborsArray.push_back(NeighborsArray());
    this->neighborsArray[this->neighborsArray.size() - 1].vector = vector;
    this->neighborsArray[this->neighborsArray.size() - 1].manhattanDistance = manhattanDistance;
}

void ExactNN::replaceNeighbor(Vector *vector, Manhattan *manhattanDistance) {
    this->neighborsArray[this->neighborsArray.size() - 1].vector = vector;
    this->neighborsArray[this->neighborsArray.size() - 1].manhattanDistance = manhattanDistance;
}

bool myfunction (NeighborsArray i, NeighborsArray j) { return ( (i.manhattanDistance)->getManhattan() < (j.manhattanDistance)->getManhattan()); }

vector<NeighborsArray> ExactNN::findExactNN(Vector *query, string outfile) {
    auto start = high_resolution_clock::now();
    for (int i = 0; i < (this->pVectorArray)->getVectorArraySize(); i++) {
        Manhattan *manhattanDistance = new Manhattan((this->pVectorArray)->getVectorArrayItem(i), query);

        //manhattanDistance->calculateDistance((this->pVectorArray)->getVectorArrayItem(i), query);
        // cout << "Q-P Distance: " << manhattanDistance->getManhattan() << endl;
        // Empty neighborsArray OR RAY exists
        if (i == 0 || (this->rayDistance != -1 && this->rayDistance >= manhattanDistance->getManhattan()))
            this->addNeighbor((this->pVectorArray)->getVectorArrayItem(i), manhattanDistance);
        // Put on neighborsArray onpy the NN
        else if (this->rayDistance == -1 && this->neighborsArray[this->neighborsArray.size() - 1].manhattanDistance->getManhattan() > manhattanDistance->getManhattan()) {
            // cout << "found new N and replace it" << endl;
            delete this->neighborsArray[this->neighborsArray.size() - 1].manhattanDistance;
            this->replaceNeighbor((this->pVectorArray)->getVectorArrayItem(i), manhattanDistance);
        }
        else {
            // cout << "Bigger N" << endl;
            delete manhattanDistance;
        }
    }
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    // Sort DESC the neighborsArray which ManhattanDistances are smaller that RAY
    if (this->rayDistance != -1)
        sort((this->neighborsArray).begin(), (this->neighborsArray).end(), myfunction);
    // this->writeNN("exactNNoutputFile.txt", query, duration.count());
    this->writeNNVerbose(outfile, query, duration.count());
    return this->neighborsArray;
}

void ExactNN::writeNN(string fileName, Vector *query, double totalTime) {
    ofstream outfile;
    outfile.open(fileName, ofstream::out | ofstream::app);

    outfile << query->getVectorID() << " ";

    for (int i = 0; i < (int)(this->neighborsArray.size()); i++)
         outfile << this->neighborsArray[i].vector->getVectorID() << " " << this->neighborsArray[i].manhattanDistance->getManhattan() << endl;

    outfile.close();
}

void ExactNN::writeNNVerbose(string fileName, Vector *query, double totalTime) {
    ofstream total;
    // total.open("exactLSHPoints.txt", ofstream::out | ofstream::app);
    total.open(fileName, ofstream::out | ofstream::app);
    // ofstream outfile;
    // outfile.open(fileName, ofstream::out | ofstream::app);

    // outfile << "Query: " << query->getVectorID() << endl;

    for (int i = 0; i < (int)(this->neighborsArray.size()); i++){
        //  outfile << "\tExact NN   : " << this->neighborsArray[i].vector->getVectorID() << "\n\tExact Dist : " << this->neighborsArray[i].manhattanDistance->getManhattan() << "\n\tExact Time : " << totalTime << endl;
         total << "\tExact NN   : " << this->neighborsArray[i].vector->getVectorID() << "\n\tExact Dist : " << this->neighborsArray[i].manhattanDistance->getManhattan() << "\n\tExact Time : " << totalTime << endl;
    }
    
    total.close();
    // outfile.close();
} 

// int main(int args, char **argv) {
//     clock_t tStart = clock();
//     Parser parser;
//     parser.parseFileInput(argv[1]);
//     VectorArray *vectorArray = parser.readFileInput(argv[1]);
//     cout << "Vector Array Time taken " << (double)(clock() - tStart) / CLOCKS_PER_SEC << endl;

//     Parser parser2;
//     parser2.parseFileInput(argv[2]);
//     VectorArray * vectorArray2 = parser2.readFileInput(argv[2]);

//     vector<ExactNN>  exactNN(parser2.getVectorArraySize(), ExactNN(vectorArray, -1));
//     for(int i=0; i<vectorArray2->getVectorArraySize(); i++) {
//         vector<NeighborsArray> exactVector = exactNN[i].findExactNN(vectorArray2->getVectorArrayItem(i));
//     }

//     delete vectorArray;
//     delete vectorArray2;
//     return 0;
// }