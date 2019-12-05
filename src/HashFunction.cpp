#include "../lib/HashFunction.h"

unsigned long int modulo(unsigned long int x, unsigned long int y){
    if(x >= 0)
        return x % y;
    else
        return x % y + y;
}

HashFunction::HashFunction(int w, int dimensionSize, int k) {
    this->w = w;
    this->k = k;
    this->s = new vector<double>[this->k];
    this->h = new vector<double>[this->k];
    //cout << "HashFunction is being created" << endl;
    default_random_engine generator;
    uniform_real_distribution<double> distribution(0.0, w);
    distribution.reset();
    for (int i = 0; i < this->k; i++) {
        this->MakeRandomSI(i, dimensionSize, w);
    }
}

void HashFunction::MakeRandomSI(int index, int dimensionSize, double w) {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    uniform_real_distribution<double> distribution(0.0, w);
    for (int j = 0; j < dimensionSize; j++) {
       ((this->s)[index]).push_back(distribution(generator));
    }
    distribution.reset();
}

HashFunction::~HashFunction(void) {
    delete [] this->s;
    delete [] this->h;
}

void HashFunction::clearKHI(void) {
    for (int i = 0; i < this->k; i++)
        this->h[i].erase(this->h[i].begin(), this->h[i].end());
}

void HashFunction::constructAI(Vector *v, int indexK) {
    this->a.clear();

    for (int i = 0; i < (int)((this->s[indexK]).size()); i++) {
        this->a.push_back(floor(((double)((v->getVectorItem(i) - ((this->s)[indexK]).at(i))) / this->w)));
    }
    // for (int i = 0; i < (int)(this->s.size()); i++) {
    //     this->a.push_back(floor(((double)((v->getVectorItem(i) - this->s[i])) / this->w)));
    // }
}

unsigned long int power(unsigned long int x, unsigned long int y, unsigned long int M) { 
    x = modulo(x, M);
    if (y == 0) 
        return 1; 
    else if (y % 2 == 0) 
        return power(x, y / 2, M) * power(x, y / 2, M); 
    else
        return x * power(x, y / 2, M) * power(x, y / 2, M); 
} 

int HashFunction::constructHI(int indexK) {
    double m = pow(2, 32);
    double M = pow(2, 32/this->k);
    unsigned long int mm = m - 5;
    unsigned long int MM = M;
    //cout << "- m " << mm << " M " << MM << " size " << (int)(this->s[indexK].size()) << endl;
    this->h[indexK].push_back(0);
    //cout << "h " << this->h[indexK].size() << endl;
    for (int i = 0; i < (int)(this->s[indexK].size()); i++) {
        //unsigned long int m_h = modulo(mm, MM); 
        //m_h = pow(m_h, i);
        unsigned long int m_h = power(mm, (int)(this->s[indexK].size()) - 1 - i, MM);
        unsigned long int ai_h = modulo(this->a[i], MM);
        //unsigned long int ai_h = this->a[i];

        //cout << "m " << m_h << ", ai " << ai_h << " -> " << m_h*ai_h << endl;
        unsigned long int m_a = m_h*ai_h;
        m_a = modulo(m_a, MM);
        // cout << "m_a " << m_a << endl;
        (this->h[indexK]).at(0) += m_a;
        //cout << "h_i " << this->h[indexK].at(0) << endl;
    }
    this->h[indexK].at(0) = modulo(this->h[indexK].at(0), MM);
    //cout << "h_i " << this->h[indexK].at(0) << endl;
    return this->h[indexK].at(0);
}

unsigned int HashFunction::constructG(){
    // Initialize g to the value of the first h(i)
    unsigned int g = this->h[0].at(0);
    for(int i = 1; i < this->k; i++) {
        // Shift value 32/k bits to the left
        g = g << 32 / (this->k);
        // Concat the next h(i)
        g = g | (int)(((this->h)[i]).at(0));
    }
    return g;
}

void HashFunction::getHashG(Vector *vector) {
    for (int i = 0; i < this->k; i++) {
        this->constructAI(vector, i);       // MAKE AIs
        //cout << (this->a).size() << endl;
        this->constructHI(i);               // MAKE k * HIs
    }
    vector->setG(this->constructG());       // MAKE G
    this->clearKHI();                       // CLEAR HIs for the next Vector
    //cout << this->h[0].size() << this->h[1].size() << this->h[2].size() << this->h[3].size() << endl;
}

// avoid
void HashFunction::printSI(int indexK) {
    ofstream outfile;
    outfile.open("SI.txt", ofstream::out | ofstream::app);

    for (int i = 0; i < (int)(this->s[indexK].size()); i++) {
        //cout << i + 1 << " " << this->s[i] << endl;
        outfile << i + 1 << " " << this->s[indexK].at(i) << endl;
    }
    outfile.close();
}
// avoid
void HashFunction::printAI(void) {
    ofstream outfile;
    outfile.open("AI.txt", ofstream::out | ofstream::app);

    //int sum = 0;
    for (int i = 0; i < (int)(this->a.size()); i++) {
        //cout << i + 1 << " " << this->a[i] << endl;
        //sum += abs(this->a[i]);
        //if (this->a[i] != -1)
            outfile << i + 1 << " " << this->a[i] << endl;
    }
    outfile << endl;
    outfile.close();
}
// avoid
int HashFunction::printSize(void) {
    //cout << "S size " << (this->s)->size();
    int sum = 0;
    for (int i = 0; i < this->k; i++)
        sum += this->s[i].size();
    //cout << " " << sum << endl;
    if (sum == (this->k)*128)
        return 1;
    else
        return 0;
    
}



// int main(int args, char **argv) {

//     Parser parser;
//     parser.parseFileInput(argv[1]);
//     VectorArray *vectorArray = parser.readFileInput(argv[1]);

//     HashFunction hashFunction(4000, 128);
//     hashFunction.printSI();
//     hashFunction.constructAI(vectorArray->getVectorArrayItem(0));
//     hashFunction.printAI();

//     delete vectorArray;

//     return 0;
// }
