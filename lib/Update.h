#ifndef UPDATE
#define UPDATE

#include <iostream>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <iterator> 
#include <unordered_map> 

#include "Initialization.h" 
#include "Distance.h" 
#include "Manhattan.h" 

using namespace std;
using namespace std::chrono;

class Update {
    private:
    public:
        Update(void);
        virtual ~Update(void);
        virtual void update(Initialization * init);
};

#endif //UPDATE