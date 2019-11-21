#include "../lib/Assignment.h"

Assignment::Assignment(void) {    
    cout << "Assignment is being created" << endl;
}

Assignment::~Assignment(void) {
    cout << "Assignment is being deleted" << endl;
}

void Assignment::setupAssignment(Initialization * init, VectorArray * vectors) {
    
}

void Assignment::printClusterItems(Initialization *init) {
    for (int i = 0; i < init->getClusterSize(); i++) {
        init->getClusterItem(i)->printClusterInfo();
    }  
}

bool Assignment::isCentroid(Vector *vector, Initialization * init) { 
    for (int i = 0; i < init->getClusterSize(); i++) {    
        if (vector->getVectorID() == init->getClusterItem(i)->getCentroid()->getVectorID())
            return true;
    }  
    return false;
}