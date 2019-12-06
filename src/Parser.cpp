#include "../lib/Parser.h"

Parser::Parser(void) {
    // cout << "Parser is being created" << endl;
    this->vectorArraySize = 0;
    this->dimensionSize = 0;
}

Parser::~Parser(void) {
    // cout << "Parser is being deleted" << endl;
}

void Parser::parseFileInput(string fileName) {
    string str;
    ifstream infile;
    infile.open(fileName);
    getline(infile, str);
    while (!infile.eof()) {
        getline(infile, str);
        // cout << str << endl << endl;
        if (vectorArraySize == 0)
            for(int i = 0; i < static_cast<int>(str.length()); i++)
                if(str[i] == '	') 
                    this->dimensionSize += 1;
        this->vectorArraySize += 1;
    }
    infile.close();
    this->vectorArraySize--;
    // this->dimensionSize--;
    // cout << "Number of points: " << this->vectorArraySize << endl;
    // cout << "Dimension: " << this->dimensionSize << endl;
}

string Parser::getFileItem(string str, int itemStart) {
    string item;
    for(int i = itemStart; str[i] != '	'; i++)
        item += str[i];
    return item;
}

VectorArray * Parser::readFileInput(string fileName) {
    double *dimension = new double[this->dimensionSize];
    bool flagId = true;
    int j = 0;
    int itemStart = 0;
    string str, id, vectorNumber;
    ifstream infile;
    infile.open(fileName);
    VectorArray *vectorArray = new VectorArray(this->vectorArraySize);
    getline(infile, str);
    while (j < this->vectorArraySize) {
        getline(infile, str);
        Vector *vector;
        for(int i = 0; i <= this->dimensionSize - 1; i++) {
            if (flagId) {
                id = this->getFileItem(str, itemStart);
                vector = new Vector(id, this->dimensionSize);
                flagId = false;
                itemStart += id.length() + 1;
                id.clear();
            }
            else {
                vectorNumber = this->getFileItem(str, itemStart);
                dimension[i-1] = stod(vectorNumber);
                itemStart += vectorNumber.length() + 1;
                vectorNumber.clear();
            }
        }
        string item;
        for(int i = itemStart; i<(int)str.length(); i++)
            item += str[i];
        dimension[this->dimensionSize - 1] = stod(item);
        vector->initVector(dimension);
        //vector->printVector();
        vectorArray->addVectorToArray(vector, j);

        flagId = true;
        //delete vector;
        itemStart = 0;
        j++;
    }
    delete[] dimension;
    vectorArray->printVectorArray();
    //delete vectorArray;
    infile.close();
    return vectorArray;
}

int Parser::getVectorArraySize(void) {
    return this->vectorArraySize;
}

int Parser::getDimensionSize(void) {
    return this->dimensionSize;
}



// int main(int args, char **argv) {
//     if(args < 3){
//         cout << "Error: Invalid command line argument.\nUsage: ./a.out <fileName>" << endl;
//         return 0;
//     }
//     // Vectors
//     Parser parser;
//     parser.parseFileInput(argv[1]);
//     VectorArray *vectorArray = parser.readFileInput(argv[1]);
//     // Queries
//     Parser parser2;
//     parser2.parseFileInput(argv[2]);
//     VectorArray *vectorArray2 = parser2.readFileInput(argv[2]);
//     // Array of Exacts, every query has its one Exact Node 
//     vector<ExactNN>  exactNN(parser2.getVectorArraySize(), ExactNN(vectorArray, atoi(argv[3])));
//     // For every query find all its neighbors 
//     for (int i = 0; i < parser2.getVectorArraySize(); i++) { 
//         exactNN[i].findExactNN(vectorArray2->getVectorArrayItem(i));
//         //exactNN[i].printNN();
//     }

//     delete vectorArray;
//     delete vectorArray2;

//     return 0;
// }


// int main(int args, char **argv) {
// //     // Parser parser;
// //     // parser.parseFileInput(argv[1]);
// //     // VectorArray *vectorArray = parser.readFileInput(argv[1]);

// //     // HashFunction hashFunction(4000, 128, 4);
// //     // //hashFunction.printSI();
// //     // for (int i = 0; i < parser.getVectorArraySize(); i++) {
// //     //     for (int j = 0; j < 4; j++){
// //     //         hashFunction.constructAI(vectorArray->getVectorArrayItem(i), j);
// //     //         hashFunction.constructHI(j);
// //     //     }
// //     //     (vectorArray->getVectorArrayItem(i))->setG(hashFunction.constructG());
// //     //     hashFunction.clearKHI();
// //     // }

// //     // delete vectorArray;


// // //////////////////////////////////////////////////////////////////////////////


//     clock_t tStart = clock();
//     Parser parser;
//     parser.parseFileInput(argv[1]);
//     VectorArray *vectorArray = parser.readFileInput(argv[1]);
//     cout << "Vector Array Time taken " << (double)(clock() - tStart) / CLOCKS_PER_SEC << endl;

//     tStart = clock();
//     //HashFunction hashFunction(4000, 128, 4);
//     LSH lsh(5, parser.getVectorArraySize()/8, 4000, parser.getDimensionSize(), 4);
//     //lsh.printLSH();
//     int counter = 0;
//     for (int i = 0; i < parser.getVectorArraySize(); i++) {
//         // if (i < 2) {
//             lsh.addItem(vectorArray->getVectorArrayItem(i));
//             counter++;
//         // }
//         if (counter == 100) {
//             cout << "ADDED " << i + 1 << " Vectors" << endl;
//             counter = 0;
//         }
//     }

//     cout << "LSH Time taken " << (double)(clock() - tStart) / CLOCKS_PER_SEC << endl;

//     Parser parser2;
//     parser2.parseFileInput(argv[2]);
//     VectorArray * vectorArray2 = parser2.readFileInput(argv[2]);
//     cout << vectorArray2->getVectorArraySize() << endl;
//     vectorArray2->getVectorArrayItem(10)->printVector();

//     for(int i=0; i<vectorArray2->getVectorArraySize(); i++) {
//         lsh.addG(vectorArray2->getVectorArrayItem(i));
//     }
//     int countTrue = 0;
//     vector<ExactNN>  exactNN(parser2.getVectorArraySize(), ExactNN(vectorArray, -1));
//     for(int i=0; i<vectorArray2->getVectorArraySize(); i++){
//         Vector * lshVector = lsh.getNN(vectorArray2->getVectorArrayItem(i));
//         vector<NeighborsArray> exactVector = exactNN[i].findExactNN(vectorArray2->getVectorArrayItem(i));
//         if (lshVector->getVectorID() == (exactVector[0].vector)->getVectorID())
//             countTrue++;
//     }
//     cout << "Found " << countTrue << " True of 100" << endl;

//     // for(int i=0; i<vectorArray2->getVectorArraySize(); i++){
//     //     cout << endl << endl;
//     //     lsh.getNNBonus(vectorArray2->getVectorArrayItem(i),2000);
//     // }

//     delete vectorArray;
//     delete vectorArray2;
//     return 0;
// }
