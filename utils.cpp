#include "utils.h"
#include <random>
#include <math.h>
#include <chrono>

double Utils::findMax(vector<vector<double>> data, unsigned i) {
    double max = 0.0;

    if (data.size() > 0 && i < data[0].size()) {
        max = data[0][i];
        for (unsigned int j = 1; j < data.size(); ++j) {
            if (max < data[j][i]) {
                max = data[j][i];
            }
        }
    }

    return max;
}

double Utils::findMin(vector<vector<double>> data, unsigned i) {
    double min = 0.0;

    if (data.size() > 0 && i < data[0].size()) {
        min = data[0][i];
        for (unsigned int j = 1; j < data.size(); ++j) {
            if (min > data[j][i]) {
                min = data[j][i];
            }
        }
    }

    return min;
}

unordered_set<double> Utils::findClasses(vector<vector<double>> data) {
    if (data.size() > 0 && data[0].size() < 3) {
        return unordered_set<double>({1});// si régression (pas de classe spécifiée)
    }

    unordered_set<double> classes;
    vector<double>* line;
    for (int i = 0; i < data.size(); ++i) {
        line = &data[i];
        classes.insert(line->back());
    }
    return classes;
}

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