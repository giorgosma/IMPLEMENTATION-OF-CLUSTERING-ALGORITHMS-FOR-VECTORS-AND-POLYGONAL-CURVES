#include "../lib/KMeansInit.h"

KMeansInit::KMeansInit(int K, VectorArray *vectorArray) : Initialization(K) {
    cout << "KMeansInit is being created" << endl;

    // points-vector = vector with all points
    // centroids-vector = []
    // centroid = uniformly selected from points-vector
    // centroids-vector.push(centroid)
    // points-vector.remove(centroid)

    // while centroids-vector.length != cluster-size
    //   dist-vector = []
    //   for each point in points-vector
    //     min = distance(points, centroid-vector[0])
    //     for each centroid in centroid-vector except the first one
    //       dist = distance(centroid, point)
    //       if min > dist
    //         min = dist
    //     dist-vector.push(min)

    //   partial-sums.push(dist-vector[0] ^ 2)
    //   for each dist in dist-vector except the first one
    //     partial-sums.push(partial-sums[partial-sums.length -1] + dist ^ 2)

    //   x = uniform(0, partial-sums[partial-sums.length -1])
    //   centroid-index = -1
    //   for r in partial-sums
    //     if r >= x
    //       centroid-index = index of r
    //       break
    //   if centroid-index = -1
    //     centroid-index = partial-sums.length - 1

    //   centroids-vector.push(points-vector[centroid-index])
    //   points-vector.remove(centroid-index)

    // points-vector = vector with all points
    vector<Vector *> * points = new vector<Vector *>;
    for(int i=0; i<vectorArray->getVectorArraySize(); i++){
        points->push_back(vectorArray->getVectorArrayItem(i));
    }

    // centroids-vector = []
    vector<Vector *> * centroids = new vector<Vector *>;

    // centroid = uniformly selected from points-vector
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    uniform_int_distribution<int> distribution(0, points->size());
    int centroid_index = distribution(generator);
    distribution.reset();
    Vector * centroid = points->at(centroid_index);

    // centroids-vector.push(centroid)
    centroids->push_back(centroid);

    // points-vector.remove(centroid)
    points->erase(points->begin() + centroid_index);

    Distance * distanceCalculator = new Manhattan();

    // while centroids-vector.length != cluster-size
    while((int)centroids->size() < K){
        // dist-vector = []
        // for each point in points-vector
        //   min = distance(points, centroid-vector[0])
        //   for each centroid in centroid-vector except the first one
        //     dist = distance(centroid, point)
        //     if min > dist
        //       min = dist
        //   dist-vector.push(min)
        vector<double> * distances = new vector<double>;
        for(int i=0; i<(int)points->size(); i++){
            double min = distanceCalculator->calculateDistance(points->at(i), centroids->at(0));
            for(int j=1; j<(int)centroids->size(); j++){
                double dist = distanceCalculator->calculateDistance(points->at(i), centroids->at(j));
                if(min > dist)
                    min = dist;
            }
            distances->push_back(min);
        }

        // partial-sums.push(dist-vector[0] ^ 2)
        // for each dist in dist-vector except the first one
        //   partial-sums.push(partial-sums[partial-sums.length -1] + dist ^ 2)
        vector<long double> * partial = new vector<long double>;
        partial->push_back(pow(distances->at(0),2));
        for(int i=1; i<(int)distances->size(); i++){
            partial->push_back(partial->at(partial->size()-1) + pow(distances->at(i),2));
        }

        // x = uniform(0, partial-sums[partial-sums.length -1])
        // centroid-index = -1
        // for r in partial-sums
        //   if r >= x
        //     centroid-index = index of r
        //     break
        // if centroid-index = -1
        //   centroid-index = partial-sums.length - 1
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        default_random_engine generator (seed);
        uniform_int_distribution<unsigned long> distribution(0, partial->at(partial->size()-1));
        unsigned long x = distribution(generator);
        distribution.reset();

        int centroid_index = -1;
        for(int i=0; i<(int)partial->size(); i++){
            if(partial->at(i) > (long double) x){
                centroid_index = i;
                break;
            }
        }
        if(centroid_index == -1)
            centroid_index = partial->size() - 1;


        // centroids-vector.push(points-vector[centroid-index])
        centroids->push_back(points->at(centroid_index));

        // points-vector.remove(centroid-index)
        points->erase(points->begin() + centroid_index);

        delete distances;
        delete partial;
    }

    for(int i=0; i<(int)centroids->size(); i++){
        this->getClusterItem(i)->initCluster(centroids->at(i)->getVectorID(), centroids->at(i)->getVectorDimension(), centroids->at(i)->getVectorCoordinates());
    }

    for(int i=0; i<this->getClusterSize(); i++){
        this->getClusterItem(i)->printClusterInfo();
    }

    delete centroids;
    delete points;
    delete distanceCalculator;
}

KMeansInit::KMeansInit(int K, VectorArray *vectorArray, Distance * distanceCalculator) : Initialization(K) {
    cout << "KMeansInit is being created" << endl;

    // points-vector = vector with all points
    // centroids-vector = []
    // centroid = uniformly selected from points-vector
    // centroids-vector.push(centroid)
    // points-vector.remove(centroid)

    // while centroids-vector.length != cluster-size
    //   dist-vector = []
    //   for each point in points-vector
    //     min = distance(points, centroid-vector[0])
    //     for each centroid in centroid-vector except the first one
    //       dist = distance(centroid, point)
    //       if min > dist
    //         min = dist
    //     dist-vector.push(min)

    //   partial-sums.push(dist-vector[0] ^ 2)
    //   for each dist in dist-vector except the first one
    //     partial-sums.push(partial-sums[partial-sums.length -1] + dist ^ 2)

    //   x = uniform(0, partial-sums[partial-sums.length -1])
    //   centroid-index = -1
    //   for r in partial-sums
    //     if r >= x
    //       centroid-index = index of r
    //       break
    //   if centroid-index = -1
    //     centroid-index = partial-sums.length - 1

    //   centroids-vector.push(points-vector[centroid-index])
    //   points-vector.remove(centroid-index)

    // points-vector = vector with all points
    vector<Vector *> * points = new vector<Vector *>;
    for(int i=0; i<vectorArray->getVectorArraySize(); i++){
        points->push_back(vectorArray->getVectorArrayItem(i));
    }

    // centroids-vector = []
    vector<Vector *> * centroids = new vector<Vector *>;

    // centroid = uniformly selected from points-vector
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    uniform_int_distribution<int> distribution(0, points->size());
    int centroid_index = distribution(generator);
    distribution.reset();
    Vector * centroid = points->at(centroid_index);

    // centroids-vector.push(centroid)
    centroids->push_back(centroid);

    // points-vector.remove(centroid)
    points->erase(points->begin() + centroid_index);

    // while centroids-vector.length != cluster-size
    while((int)centroids->size() < K){
        // dist-vector = []
        // for each point in points-vector
        //   min = distance(points, centroid-vector[0])
        //   for each centroid in centroid-vector except the first one
        //     dist = distance(centroid, point)
        //     if min > dist
        //       min = dist
        //   dist-vector.push(min)
        vector<double> * distances = new vector<double>;
        for(int i=0; i<(int)points->size(); i++){
            double min = distanceCalculator->calculateDistance(points->at(i), centroids->at(0));
            for(int j=1; j<(int)centroids->size(); j++){
                double dist = distanceCalculator->calculateDistance(points->at(i), centroids->at(j));
                if(min > dist)
                    min = dist;
            }
            distances->push_back(min);
        }

        // partial-sums.push(dist-vector[0] ^ 2)
        // for each dist in dist-vector except the first one
        //   partial-sums.push(partial-sums[partial-sums.length -1] + dist ^ 2)
        vector<long double> * partial = new vector<long double>;
        partial->push_back(pow(distances->at(0),2));
        for(int i=1; i<(int)distances->size(); i++){
            partial->push_back(partial->at(partial->size()-1) + pow(distances->at(i),2));
        }

        // x = uniform(0, partial-sums[partial-sums.length -1])
        // centroid-index = -1
        // for r in partial-sums
        //   if r >= x
        //     centroid-index = index of r
        //     break
        // if centroid-index = -1
        //   centroid-index = partial-sums.length - 1
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        default_random_engine generator (seed);
        uniform_int_distribution<unsigned long> distribution(0, partial->at(partial->size()-1));
        unsigned long x = distribution(generator);
        distribution.reset();

        int centroid_index = -1;
        for(int i=0; i<(int)partial->size(); i++){
            if(partial->at(i) > (long double) x){
                centroid_index = i;
                break;
            }
        }
        if(centroid_index == -1)
            centroid_index = partial->size() - 1;


        // centroids-vector.push(points-vector[centroid-index])
        centroids->push_back(points->at(centroid_index));

        // points-vector.remove(centroid-index)
        points->erase(points->begin() + centroid_index);

        delete distances;
        delete partial;
    }

    for(int i=0; i<(int)centroids->size(); i++){
        this->getClusterItem(i)->initCluster(centroids->at(i)->getVectorID(), centroids->at(i)->getVectorDimension(), centroids->at(i)->getVectorCoordinates());
    }

    for(int i=0; i<this->getClusterSize(); i++){
        this->getClusterItem(i)->printClusterInfo();
    }

    delete centroids;
    delete points;
}

KMeansInit::~KMeansInit(void) {
    cout << "KMeansInit is being deleted" << endl;
}

// void KMeansInit::getClusterSize(void) {
//     cout << "KMeansInit ClusterSize "  << endl;
//     Initialization::getClusterSize();
// }
