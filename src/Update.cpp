#include "../lib/Update.h"

Update::Update(void) {    
    cout << "Update is being created" << endl;
}

Update::~Update(void) {
    cout << "Update is being deleted" << endl;
}

void Update::update(Initialization * init){
    cout << "update() running on Update object" << endl;
}