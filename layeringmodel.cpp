#include "layeringmodel.h"
#include <random>
#include <math.h>
#include <chrono>

LayeringModel::LayeringModel(vector<vector<double>> dataset, vector<ActivationFunction*> activation)
{
	this->dataset = dataset;
    this->aFunction = activation;
}


vector<double> LayeringModel::generateRandom(int size) {
    vector<double> rand = vector<double>(size);

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    normal_distribution<double> distribution(0., 1.);

    for (unsigned i = 0; i < size; i++) {
        rand[i] = distribution(generator);
    }
    return rand;

}