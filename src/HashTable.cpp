#include "../lib/HashTable.h"

HashTable::HashTable(int size, int w, int dimensionSize, int k) {
    //cout << "HashTable is being created" << endl;
    this->size = size;
    this->buckets = new vector<Vector *>[size];
    this->hashFunction = new HashFunction(w, dimensionSize, k);
}

HashTable::~HashTable(void) {
    delete[] this->buckets;
    delete this->hashFunction;
}

void HashTable::print(void) {
    cout << "HashTable size is " << this->size << endl;
    for(int i=0; i<this->size; i++){
        cout << "Bucket #" << i << " has size " << this->buckets[i].size() << " (";
        for(int j=0; j<(int)(this->buckets[i].size()); j++){
            if(j == (int)(this->buckets[i].size()) - 1)
                cout << ((this->buckets)[i]).at(j)->getVectorID();
            else
                cout << ((this->buckets)[i]).at(j)->getVectorID() << ", ";
        }
            cout << ")" << endl;
    }
}

bool HashTable::add(int bucket, Vector * pointer){
    this->buckets[bucket].push_back(pointer);
    return true;
}

vector<Vector *> * HashTable::getBucket(int bucket){
    return &this->buckets[bucket];
}

int HashTable::getTableSize() {
    return this->size;
}

void HashTable::storeVector(Vector *vector, int Lnumber) {
    (this->hashFunction)->getHashG(vector); // CALCULATE G FOR L[i] HASHTABLE, Lnumber is the index of L HASHTABLES

    unsigned int g = vector->getG(Lnumber); // GET g FOR L[i] HASHTABLE

    this->add(g % this->size, vector);      // ADD Vector to index g of HASHTABLE
}

void HashTable::addG(Vector *vector) {
    (this->hashFunction)->getHashG(vector);
}

void HashTable::accessHashTable(unsigned int g) {
    cout << "Bucket " << g % this->size << " G " << g << " ID " << (this->buckets[g % this->size].at(0))->getVectorID() << endl;
}

// avoid
int modulo(int x, int y){
    if(x >= 0)
        return x % y;
    else
        return x % y + y;
}
// avoid
int getG(int * h, int size, int k){
    // Initialize g to the value of the first h(i)
    int g = h[0];
    for(int i=1; i<size; i++){
        // Shift value 32/k bits to the left
        g = g << 32/k;
        // Concat the next h(i)
        g = g | h[i];
    }
    return g;
}

// int main(int args, char **argv) {

//     int size = 12;

//     HashTable * hashTable = new HashTable(size);

//     double dimensions[10] = {1,2,3,4,5,6,7,8,9,0};
//     Vector * vector1 = new Vector("1", 10);
//     vector1->initVector(dimensions);
//     Vector * vector2 = new Vector("2", 10);
//     vector2->initVector(dimensions);
//     Vector * vector3 = new Vector("3", 10);
//     vector3->initVector(dimensions);
//     Vector * vector4 = new Vector("4", 10);
//     vector4->initVector(dimensions);
//     Vector * vector5 = new Vector("5", 10);
//     vector5->initVector(dimensions);
//     Vector * vector6 = new Vector("6", 10);
//     vector6->initVector(dimensions);

//     hashTable->add(1, vector1);
//     hashTable->add(3, vector2);
//     hashTable->add(3, vector3);
//     hashTable->add(3, vector4);
//     hashTable->add(6, vector5);
//     hashTable->add(6, vector6);

//     hashTable->print();

//     vector<Vector *> * someBucket = hashTable->getBucket(6);
//     for(int i=0; i<someBucket->size(); i++){
//         cout << someBucket->at(i)->getVectorID() << endl;
//     }

//     delete hashTable;
//     delete vector1;
//     delete vector2;
//     delete vector3;
//     delete vector4;
//     delete vector5;
//     delete vector6;

//     cout << modulo(10,2) << endl;
//     cout << modulo(-7,3) << endl;
//     cout << modulo(-21,4) << endl;

//     int h[10] = {1,2,3,4,5,6,7,8,9,0};
//     cout << getG(h, 10, 4) << endl;

//     bitset<32> x(getG(h, 10, 4));
//     cout << x << endl;

//     return 0;
// }
