#include "../lib/VectorArray.h"

VectorArray::VectorArray(int size) {
    this->size = size;
    this->vectorArray = new Vector*[size];
    cout << "VectorArray is being created" << endl;
}

VectorArray::~VectorArray(void) {
    cout << "VectorArray is being deleted" << endl;
    for (int i = 0; i < this->size; i++)
        delete this->vectorArray[i];
    delete[] this->vectorArray;
}

void VectorArray::addVectorToArray(Vector *vector, int index) {
    (this->vectorArray)[index] = vector;
}

void VectorArray::printVectorArray(void) {
    // for (int i = 0; i < this->size; i++) {
    //     cout << "Array [" << i << "] => ";
    //     (this->vectorArray)[i]->printVector();
    // }
    // cout << endl; 
}

Vector * VectorArray::getVectorArrayItem(int index) {
    return (this->vectorArray)[index];
}

int VectorArray::getVectorArraySize(void) {
    return this->size;
}
