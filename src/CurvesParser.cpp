#include "../lib/CurvesParser.h"

using namespace std;

CurvesParser::CurvesParser(void) {
    cout << "CurvesParser is being created" << endl;
}

CurvesParser::~CurvesParser(void) {
    cout << "CurvesParser is being deleted" << endl;
    for (int i = 0; i < (int)(this->curves->size()); i++){
        delete this->curves->at(i);
    }
    delete this->curves;
}

int CurvesParser::countLines(char * fileName){
    string str;
    int count = -1;
    ifstream infile;
    infile.open(fileName);
    while (!infile.eof()) {
        getline(infile, str);
        count += 1;
    }
    infile.close();
    return count;
}

string CurvesParser::getNext(string line, int start, char breakChar){
    string next;
    for(int i=start; line[i] != breakChar; i++){
        next += line[i];
    }
    return next;
}

vector<double> * CurvesParser::parseLine(string line){
    int curPos = 0;
    string next;
    int count;

    // Get ID
    next = getNext(line, curPos, '\t');
    curPos += next.length() + 1;

    // Get point count
    next = getNext(line, curPos, '\t');
    curPos += next.length() + 1;
    count = stoi(next);

    // Get points
    vector<double> * points = new vector<double>;
    for(int i=0; i<count; i++){
        next = getNext(line, curPos, ')');
        curPos += next.length() + 1;

        string first, second;
        bool flag = false;
        for(int j=1; j<(int)(next.length()); j++){
            if(next[j] == ','){
                flag = true;
                j += 2;
            }
            if(!flag){
                first += next[j];
            }
            else{
                second += next[j];
            }
        }

        if(first[0] == '('){
            string newFirst;
            for(int i=1; i<(int)(first.length()); i++){
                newFirst += first[i];
            }
            first = newFirst;
        }

        double x, y;
        x = stod(first);
        y = stod(second);
        points->push_back(x);
        points->push_back(y);
    }
    return points;
}

vector<vector<double> *> * CurvesParser::parseFile(char * fileName){
    // vector<vector<double> *> * curves = new vector<vector<double> *>;
    this->curves = new vector<vector<double> *>;
    string str;
    ifstream infile;
    infile.open(fileName);
    getline(infile, str);
    cout << str << endl;
    while (!infile.eof()) {
        getline(infile, str);
        if(str.length() < 1) break;

        vector<double> * points = parseLine(str);
        (this->curves)->push_back(points);
    }
    infile.close();
    return this->curves;

}

VectorArray * CurvesParser::storeCurvesIntoVectorArray(vector<vector<double> *> * curves) {
    cout << "Curves Size : " << curves->size() << endl;
    VectorArray *vectorArray = new VectorArray(curves->size());
    for (int i = 0; i < vectorArray->getVectorArraySize(); i++) {
        double *array = &(curves->at(i)->at(0));
        Vector * vector = new Vector(to_string(i), curves->at(i)->size());
        vector->initVector(array);
        vectorArray->addVectorToArray(vector, i);
    }
    return vectorArray;
}