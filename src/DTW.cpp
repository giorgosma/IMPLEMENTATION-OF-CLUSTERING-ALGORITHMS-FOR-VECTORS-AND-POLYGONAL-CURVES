#include "../lib/DTW.h"

DTW::DTW(void) {    
}

DTW::~DTW(void) {
}

double DTW::calculateDistance(vector<double> * p, vector<double> * q){
    this->array.clear();
    this->distance = this->C(*p, *q, p->size()/2, q->size()/2);
    return this->distance;
}

double DTW::getDTW(void) {
    return this->distance;
}

double DTW::euclidean(vector<double> p, vector<double> q, int i, int j) {
    //cout << "P " << i << " Q " << j << endl;
    i--;
    j--;
    i = i*2;
    j = j*2;
    //cout << "Pi " << i << " Qj " << j << endl;
    double dist = 0;
    for (int k = 0; k <= 1; k++) {
        //cout << "Get" << i + k << ", " << j + k << endl; 
        dist += pow(abs(p[i + k ] - q[j + k]), 2);
    }
    return sqrt(dist);
}

double DTW::C(vector<double> p, vector<double> q, int i, int j) {
    //cout << "I " << i << " J " << j << endl; 
    unordered_map<string, double>::iterator it;
    string ij = to_string(i) + to_string(j);
    it = (this->array).find(ij);
    if (i == 1 && j == 1) {
        if (it == (this->array).end()) {
            (this->array)[ij] = this->euclidean(p, q, i, j);
            return (this->array)[ij];
        }
        else 
            return it->second;
        // return this->euclidean(p, q, i, j);
    }
    else if (i > 1 && j == 1) {
        if (it == (this->array).end()) {
            (this->array)[ij] = this->euclidean(p, q, i, j);
            (this->array)[ij] += this->C(p, q, i-1, j);
            return (this->array)[ij];
        }
        else 
            return it->second;
        // return this->C(p, q, i-1, j) + this->euclidean(p, q, i, j);
    }
    else if (j > 1 && i == 1) {
        if (it == (this->array).end()) {
            (this->array)[ij] = this->euclidean(p, q, i, j);
            (this->array)[ij] += this->C(p, q, i, j-1);
            return (this->array)[ij];
        }
        else 
            return it->second;
        // return this->C(p, q, i, j-1) + this->euclidean(p, q, i, j);
    }
    else {
        if (it == (this->array).end()) {
            double x1 = this->C(p, q, i-1, j);
            double x2 = this->C(p, q, i-1, j-1);
            double x3 = this->C(p, q, i, j-1);
            double minX = min(x1, x2);
            minX = min(minX, x3);
            (this->array)[ij] = this->euclidean(p, q, i, j);
            (this->array)[ij] += minX;
            // cout << minX + this->euclidean(p, q, i, j) << endl;
            return minX + this->euclidean(p, q, i, j);
        }
        else 
            return it->second;
    }
}

vector<double> DTW::padding(vector<double> smallCurve, int bigSize) {
    vector<double> newCurve;
    for (int i = 0; i < bigSize; i++) {
        if (i < (int)(smallCurve.size()))
            newCurve.push_back((smallCurve)[i]);
        else 
            newCurve.push_back(0);
    }
    return newCurve;
}

// int main (int args, char **argv) {
//     vector<double> P;
//     vector<double> Q;
    
//     P.push_back(1.0);
//     P.push_back(3.0);
//     P.push_back(5.0);
//     P.push_back(7.0);
//     P.push_back(1.0);
//     P.push_back(3.0);
//     P.push_back(5.0);
//     P.push_back(7.0);
//     P.push_back(1.0);
//     P.push_back(3.0);
//     P.push_back(5.0);
//     P.push_back(7.0);
//     P.push_back(1.0);
//     P.push_back(3.0);
//     P.push_back(5.0);
//     P.push_back(7.0);
//     // for (int i = 0; i < (int)(P.size()); i++) {
//     //     cout << "P " << P[i] << endl;
//     // }

//     Q.push_back(2.0);
//     Q.push_back(4.0);
//     Q.push_back(6.0);
//     Q.push_back(8.0);
//     Q.push_back(10.0);
//     Q.push_back(12.0);
//     Q.push_back(2.0);
//     Q.push_back(4.0);
//     Q.push_back(6.0);
//     Q.push_back(8.0);
//     Q.push_back(10.0);
//     Q.push_back(12.0);
//     Q.push_back(2.0);
//     Q.push_back(4.0);
//     Q.push_back(6.0);
//     Q.push_back(8.0);
//     Q.push_back(10.0);
//     Q.push_back(12.0);
//     Q.push_back(2.0);
//     Q.push_back(4.0);
//     Q.push_back(6.0);
//     Q.push_back(8.0);
//     Q.push_back(10.0);
//     Q.push_back(12.0);
//     // for (int i = 0; i < (int)(Q.size()); i++) {
//     //     cout << "Q " << Q[i] << endl;
//     // }

//     DTW dtw;

//     auto start = high_resolution_clock::now(); 

//     dtw.calcDistance(&P, &Q);

//     dtw.calcDistance(&P, &Q);

//     dtw.calcDistance(&P, &Q);

//     dtw.calcDistance(&P, &Q);

//     dtw.calcDistance(&P, &Q);

//     auto stop = high_resolution_clock::now(); 

//     auto duration = duration_cast<microseconds>(stop - start); 
  
//     cout << "Time taken by function: " << duration.count() << " microseconds" << endl; 

// }