#include "../lib/Grids.h"

Grids::Grids(int L, double delta, double maxT) {
    this->L = L;
    this->delta = delta;
    this->generateT(maxT);
}

Grids::~Grids(void) {
}

void Grids::printT(){
    for(int i=0; i<(int)(this->t.size()); i++){
        cout << this->t.at(i) << endl;
    }
}

void Grids::generateT(double maxT) { 
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    uniform_real_distribution<double> distribution(0.0, maxT);
    for (int j = 0; j < this->L; j++) {
       (this->t).push_back(distribution(generator));
    }
    distribution.reset();
}

vector<vector<vector<double> *> *> * Grids::projectToGrids(vector<vector<double> *> * curves) {
    cout << "projectToGrids received a vector with " << curves->size() << " curves" << endl;

    vector<vector<vector<double> *> *> * allGrids = new vector<vector<vector<double> *> *>;

    for(int i=0; i<this->L; i++){
        vector<vector<double> *> * grid = new vector<vector<double> *>;
        double dt = this->delta * this->t.at(i);
                                                                            cout << "Working with delta=" << this->delta << " and t=" << this->t.at(i) << " (dt=" << dt << ")" << endl;
        for(int j=0; j< (int)(curves->size()); j++){
            grid->push_back(new vector<double>);
            for(int k=0; k<(int)(curves->at(j)->size()); k+=2){
                double x = round(curves->at(j)->at(k) / dt);
                double y = round(curves->at(j)->at(k+1) / dt);

                if(k != 0){
                    if(x == grid->at(j)->at(grid->at(j)->size() - 2) && y == grid->at(j)->at(grid->at(j)->size() - 1)){
                        continue;
                    }
                }

                grid->at(j)->push_back(x);
                grid->at(j)->push_back(y);

                // cout << curves->at(j)->at(k) << endl;
                // cout << curves->at(j)->at(k) / dt << endl;
                // cout << grid->at(j)->at(grid->at(j)->size() - 2) << endl << endl;
                // cout << curves->at(j)->at(k+1) << endl;
                // cout << curves->at(j)->at(k+1) / dt << endl;
                // cout << grid->at(j)->back() << endl << endl;
            }
        }
        allGrids->push_back(grid);
    }

    // Padding
    for(int i=0; i<this->L; i++){
        int max = 0;
        for(int j=0; j<(int)(allGrids->at(i)->size()); j++){
            if((int)(allGrids->at(i)->at(j)->size()) > max){
                max = allGrids->at(i)->at(j)->size();
            }
        }
        for(int j=0; j<(int)(allGrids->at(i)->size()); j++){
            for(int k=allGrids->at(i)->at(j)->size(); k<max; k++){
                allGrids->at(i)->at(j)->push_back(0);
            }
        }
    }

    return allGrids;
}

double Grids::accessGrid(vector<vector<vector<double> *> *> * grid, int L, int curveID, int p){
    return grid->at(L)->at(curveID)->at(p);
}
