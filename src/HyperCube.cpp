#include "../lib/HyperCube.h"

HyperCube::HyperCube(int dimensionSize, int w, int k, int dTon, int M, int probes) {
    this->dimension = dimensionSize;
    this->w = w;
    this->k = k;
    this->size = pow(2, dTon);
    this->fArray = new map<unsigned int,unsigned int>[dTon];
    this->dTon = dTon;
    this->M = M;
    this->probes = probes;

}

HyperCube::~HyperCube(void) {
    //delete this->hashFunction;
    delete[] this->fArray;
}

void HyperCube::constructVerticle(Vector *vector) {
    for (int i = 0; i < this->dTon; i++) {      // Calculate dTon Gi and Store them into Vector's G Array
        this->hashFunction = new HashFunction(this->w, this->dimension, this->k);
        (this->hashFunction)->getHashG(vector);
        delete this->hashFunction;
    }
}

void HyperCube::insertNewVector(Vector *vector) {
    this->constructVerticle(vector);
    string index = this->getVerticle(vector);   // Get Vericle 010101...
    this->HashTable[index].push_back(vector);   // access HashTable via Verticle index
    //cout << "HT [ " << index << " ] \t -> " << this->HashTable[index].size() << endl;
}

void HyperCube::printHashTableSize() {
    int sum = 0;
    unordered_map<string, vector<Vector *>>:: iterator itr;
    for (itr = (this->HashTable).begin(); itr != (this->HashTable).end(); itr++) {  
        cout << itr->first << "  " << itr->second.size() << endl; 
        sum += itr->second.size();
    } 
    //cout << "Added " << sum << endl;
}

string HyperCube::getVerticle(Vector *vector) {
    string verticle = "";
    for (int i = 0; i < this->dTon; i++) {
        unsigned int g = vector->getG(i);
        map<unsigned int, unsigned int>::iterator it;
        it = (this->fArray[i]).find(g);                                             // IF Gi already exists into MAP [G, F(G)]
        if (it == (this->fArray[i]).end()) 
        {
            unsigned seed = chrono::system_clock::now().time_since_epoch().count();
            default_random_engine generator (seed);
            uniform_int_distribution<int> distribution(0, 1);
            (this->fArray[i]).insert(pair<unsigned int,unsigned int>(g, distribution(generator)));
        }  
        //    (this->fArray[i]).insert(pair<unsigned int,unsigned int>(g, g % 2));    // TODO CHANGE MOD 2 TO UNIFORM RANDOM
        
        //cout << "G [ " << i <<" ] : " << g << " \t F ( G ) : " << (this->fArray[i]).find(g)->second  << endl;
        verticle += to_string((this->fArray[i]).find(g)->second);
    }
    //cout << "ID " << vector->getVectorID() << " Vericle " << verticle << endl;      // Add Fi to construct Verticle
    return verticle;
}

Vector * HyperCube::getNN(Vector *query) {
    ofstream total;
    total.open("exactHyperCubePoints.txt", ofstream::out | ofstream::app);
    //ofstream outfile;
    //outfile.open("HyperCubeoutputFile.txt", ofstream::out | ofstream::app);

    //cout << "Query: " << query->getVectorID() << endl;
    // outfile << "Query: " << query->getVectorID() << endl;
    total << "Query: " << query->getVectorID() << endl;

    // clock_t tStart = clock();
    auto start = high_resolution_clock::now();

    this->constructVerticle(query);
    string indexVerticle = this->getVerticle(query);
    // cout << "Query verticle : " << indexVerticle << endl; 
    Vector *NN = NULL;
    int min = 2147483647;

    unordered_map<string, vector<Vector *>>::iterator it;
    int countComparisons = 0;
    it = (this->HashTable).find(indexVerticle);
    if (it != (this->HashTable).end())
        for (int i = 0; i < (int)((it->second).size()); i++) {
            if (countComparisons > (this->M))
                break;
            Manhattan *manhattanDistance = new Manhattan(query, (it->second)[i]);
            int dist = manhattanDistance->getManhattan();
            delete manhattanDistance;
            if (dist < min) {
                min = dist;
                NN = (it->second)[i];
            }
            countComparisons++;
        }
    // else 
    //     cout << "Not Found Verticle in HT " << indexVerticle << endl;

    int countNeighbors = 0;
    for (int i = 0; i < this->dTon; i++) {
        if (countNeighbors > this->probes)
            break;
        string neighborVerticle = this->getNeighborVerticle(indexVerticle, i);
        // cout << "Search for : " << neighborVerticle << endl;
        unordered_map<string, vector<Vector *>>::iterator it;
        it = (this->HashTable).find(neighborVerticle);
        if (it == (this->HashTable).end())
            continue;
        countComparisons = 0;
        for (int i = 0; i < (int)((it->second).size()); i++) {
            if (countComparisons > (this->M))
                break;
            Manhattan *manhattanDistance = new Manhattan(query, (it->second)[i]);
            int dist = manhattanDistance->getManhattan();
            delete manhattanDistance;
            if (dist < min) {
                min = dist;
                NN = (it->second)[i];
            }
            countComparisons++;
        }
        countNeighbors++;
    }
    // double totalTime = (double)(clock() - tStart) / CLOCKS_PER_SEC;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    if (NN == NULL) {
        // cout << "\tHyperCube NN     : -" << endl;
        // cout << "\tHyperCube Dist   : -" << endl;
        // cout << "\tHyperCube Time   : " << duration.count() << endl;
        // outfile << "\tHyperCube NN     : -" << endl;
        // outfile << "\tHyperCube Dist   : -" << endl;
        // outfile << "\tHyperCube Time   : " << duration.count() << endl;
        total << "\tHyperCube NN     : -" << endl;
        total << "\tHyperCube Dist   : -" << endl;
        total << "\tHyperCube Time   : " << duration.count() << endl;
    }
    else {
        // cout << "\tHyperCube NN     : " << NN->getVectorID() << endl;
        // cout << "\tHyperCube Dist   : " << min << endl;
        // cout << "\tHyperCube Time   : " << duration.count() << endl;
        // outfile << "\tHyperCube NN     : " << NN->getVectorID() << endl;
        // outfile << "\tHyperCube Dist   : " << min << endl;
        // outfile << "\tHyperCube Time   : " << duration.count() << endl;
        total << "\tHyperCube NN     : " << NN->getVectorID() << endl;
        total << "\tHyperCube Dist   : " << min << endl;
        total << "\tHyperCube Time   : " << duration.count() << endl;
    }
    // outfile.close();
    total.close();
    return NN;
}

vector <Vector *> HyperCube::getNNBonus(Vector *query, int r) {
    
    ofstream outfile;
    outfile.open("HyperCubePointsBonus.txt", ofstream::out | ofstream::app);

    //cout << "Query: " << query->getVectorID() << endl;
    outfile << "Query: " << query->getVectorID() << endl;

    // this->constructVerticle(query);
    string indexVerticle = this->getVerticle(query);
    //cout << "BONUS " << indexVerticle << endl;
    vector <Vector *> NN;

    unordered_map<string, vector<Vector *>>::iterator it;
    it = (this->HashTable).find(indexVerticle);
    for (int i = 0; i < (int)((it->second).size()); i++) {
        Manhattan *manhattanDistance = new Manhattan(query, (it->second)[i]);
        int dist = manhattanDistance->getManhattan();
        delete manhattanDistance;
        if(dist < r){
            NN.push_back((it->second)[i]);
        }
    }

    for (int i = 0; i < this->dTon; i++) {
        string neighborVerticle = this->getNeighborVerticle(indexVerticle, i);
        unordered_map<string, vector<Vector *>>::iterator it;
        it = (this->HashTable).find(neighborVerticle);
        for (int i = 0; i < (int)((it->second).size()); i++) {
            Manhattan *manhattanDistance = new Manhattan(query, (it->second)[i]);
            int dist = manhattanDistance->getManhattan();
            delete manhattanDistance;
            if(dist < r){
                NN.push_back((it->second)[i]);
            }
        }
    }
    if(NN.size() == 0) {
        // cout << "No NN found" << endl;
        outfile << "\tHyperCube NN     : -" << endl;
    }
    else {
        // cout << "Found " << NN.size()  << " neighbors within a radius of " << r << endl;
        for (int i = 0; i < (int)(NN.size()); i++) {
            outfile << "\tHyperCube NN     : " << NN[i]->getVectorID() << endl;
        }
    }
    return NN;
}

string HyperCube::getNeighborVerticle(string verticle, int index) {
    if (verticle[index] == '0')
        verticle[index] = '1';
    else 
        verticle[index] = '0';
    return verticle;
}

vector<string> HyperCube::getBucketVectorsID(Vector * query) {
    vector<string> bucketIDs;
    // vector <Vector *> * bucket;

    this->constructVerticle(query);
    string indexVerticle = this->getVerticle(query);
    // cout << "Query verticle : " << indexVerticle << endl; 
    // Vector *NN = NULL;
    // int min = 2147483647;

    unordered_map<string, vector<Vector *>>::iterator it;
    int countComparisons = 0;
    it = (this->HashTable).find(indexVerticle);
    if (it != (this->HashTable).end())
        for (int i = 0; i < (int)((it->second).size()); i++) {
            if (countComparisons > (this->M))
                break;
            bucketIDs.push_back(((it->second)[i])->getVectorID());
            countComparisons++;
        }
    else 
        cout << "Not Found Verticle in HT " << indexVerticle << endl;

    int countNeighbors = 0;
    for (int i = 0; i < this->dTon; i++) {
        if (countNeighbors > this->probes)
            break;
        string neighborVerticle = this->getNeighborVerticle(indexVerticle, i);
        // cout << "Search for : " << neighborVerticle << endl;
        unordered_map<string, vector<Vector *>>::iterator it;
        it = (this->HashTable).find(neighborVerticle);
        if (it == (this->HashTable).end())
            continue;
        countComparisons = 0;
        for (int i = 0; i < (int)((it->second).size()); i++) {
            if (countComparisons > (this->M))
                break;
            bucketIDs.push_back(((it->second)[i])->getVectorID());
            countComparisons++;
        }
        countNeighbors++;
    }

    return bucketIDs;
}

// int main (int args, char **argv) {
//     clock_t tStart = clock();
//     Parser parser;
//     parser.parseFileInput(argv[1]);
//     VectorArray *vectorArray = parser.readFileInput(argv[1]);
//     cout << "Vector Array Time taken " << (double)(clock() - tStart) / CLOCKS_PER_SEC << endl;

//     tStart = clock();
//     HyperCube hp(parser.getDimensionSize(), 4000, 4, 4, 500, 4);
//     int counter = 0;
//     for (int i = 0; i < parser.getVectorArraySize(); i++) {
//         //if (i < 500) {
//             hp.insertNewVector(vectorArray->getVectorArrayItem(i));
//             counter++;
//         //}
//         if (counter == 100) {
//             cout << "ADDED " << i + 1 << " Vectors"<< endl;
//             counter = 0;
//         }
//     }
//     cout << "HyperCube Time taken " << (double)(clock() - tStart) / CLOCKS_PER_SEC << endl;
//     hp.printHashTableSize();

//     Parser parser2;
//     parser2.parseFileInput(argv[2]);
//     VectorArray * vectorArray2 = parser2.readFileInput(argv[2]);

//     int countTrue = 0;
//     vector<ExactNN>  exactNN(parser2.getVectorArraySize(), ExactNN(vectorArray, -1));
//     for (int i = 0; i < vectorArray2->getVectorArraySize(); i++) {
//         Vector * hpVector = hp.getNN(vectorArray2->getVectorArrayItem(i));
//         vector<NeighborsArray> exactVector = exactNN[i].findExactNN(vectorArray2->getVectorArrayItem(i));
//         if (hpVector != NULL)
//             if (hpVector->getVectorID() == (exactVector[0].vector)->getVectorID())
//                 countTrue++;

//     }
//     cout << "Found " << countTrue << " True of 100" << endl;
//     // for (int i = 0; i < vectorArray2->getVectorArraySize(); i++) {
//     //     cout << endl << endl;
//     //     hp.getNNBonus(vectorArray2->getVectorArrayItem(i), 2000);
//     // }

//     delete vectorArray;
//     delete vectorArray2;
//     return 0;
// }