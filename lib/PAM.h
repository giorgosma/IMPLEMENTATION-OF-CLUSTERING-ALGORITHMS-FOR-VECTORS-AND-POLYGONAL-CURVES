#include <iostream>
#include <cmath>
#include "Update.h"
#include <algorithm>
#include <chrono>
#include <random>
#include <iterator> 
#include <unordered_map> 

using namespace std;
using namespace std::chrono;

class PAM : public Update{
    private:

    public:
        PAM(void);
        ~PAM(void);
        void update(Initialization * init);
};