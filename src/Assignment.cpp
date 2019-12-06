#include "../lib/Assignment.h"

Assignment::Assignment(void) {    
    // cout << "Assignment is being created" << endl;
}

Assignment::~Assignment(void) {
    // cout << "Assignment is being deleted" << endl;
}

void Assignment::setupAssignment(Initialization * init, VectorArray * vectors) {
    
}

void Assignment::printClusterItems(Initialization *init) {
    cout << "Cluster Sizes: ";
    for (int i = 0; i < init->getClusterSize()-1; i++) {
        init->getClusterItem(i)->printClusterInfo();
        cout << ", ";
    }
    init->getClusterItem(init->getClusterSize()-1)->printClusterInfo();
    cout << endl;
}

bool Assignment::isCentroid(Vector *vector, Initialization * init) { 
    for (int i = 0; i < init->getClusterSize(); i++) {    
        if (vector->getVectorID() == init->getClusterItem(i)->getCentroid()->getVectorID())
            return true;
    }  
    return false;
}
