#include "utils.h"

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
