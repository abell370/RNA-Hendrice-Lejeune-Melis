#include "utils.h"
#include <random>
#include <math.h>
#include <chrono>

vector<double> Utils::calcDecisionLine(vector<double> weights, vector<double> x) {
    vector<double> line;
    for (double value : x) {
        line.push_back(0);
    }
    return line;
}


vector<double> Utils::generateRandom(int size) {
    vector<double> rand = vector<double>(size);

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    normal_distribution<double> distribution(0., 1.);

    for (unsigned i = 0; i < size; i++) {
        rand[i] = distribution(generator);
    }
    return rand;

}