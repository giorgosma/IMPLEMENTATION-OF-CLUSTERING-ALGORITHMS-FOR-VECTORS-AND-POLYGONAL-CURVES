#include "../lib/Manhattan.h"

Manhattan::Manhattan(Vector *p, Vector *q) {
    // cout << "Manhattan is being created" << endl;
    //this->distance = -1;
    this->distance = 0;
    for (int i = 0; i < p->getVectorDimension(); i++) {
        this->distance += abs(p->getVectorItem(i) - q->getVectorItem(i));
    }
}

Manhattan::~Manhattan(void) {
    // cout << "Manhattan is being deleted" << endl;
}

void Manhattan::calculateDistance(Vector *p, Vector *q) {   // Maybe its going to be killed
    // this->distance = sum ( |p->x_I - q->x_I|)
    this->distance = 0;
    for (int i = 0; i < p->getVectorDimension(); i++) {
        this->distance += abs(p->getVectorItem(i) - q->getVectorItem(i));
    }
}

int Manhattan::getManhattan(void) {
    return this->distance;
}

