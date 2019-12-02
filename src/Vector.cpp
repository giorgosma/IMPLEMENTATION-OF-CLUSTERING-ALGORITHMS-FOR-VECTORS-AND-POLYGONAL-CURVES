#include "../lib/Vector.h"

Vector::Vector(string id, int size) {
    this->size = size;
    this->dimension = new double[size];
    this->id = id;
    //this->g = -1;
    //cout << "Vector is being created with id: " << this->id  << endl;
}

Vector::~Vector(void) {
    //cout << "Vector is being deleted" << endl;
    delete[] this->dimension;
}

void Vector::initVector(double *dimension) {
    for (int i = 0; i < this->size; i++) {
        this->dimension[i] = dimension[i];
    }
}

void Vector::printVector() {
    cout << "ID " << this->id << "[ ";
    for (int i = 0; i < this->size; i++)
        cout << this->dimension[i] << " ";
    cout << "]" << endl; 
}

int Vector::getVectorDimension(void) {
    return this->size;
}

double Vector::getVectorItem(int index) {
    return this->dimension[index];
}

double * Vector::getVectorCoordinates() {
    return this->dimension;
}

string Vector::getVectorID(void) {
    return this->id;
}

void Vector::setG(unsigned int g) {
    this->g.push_back(g);
}

unsigned int Vector::getG(int index) {
    return this->g.at(index);
}

vector<unsigned int> * Vector::getG() {
    return &(this->g);
}

double * Vector::getDimension(void){
    return this->dimension;
}

int Vector::getSize(void){
    return this->size;
}

string Vector::getID(void){
    return this->id;
}
