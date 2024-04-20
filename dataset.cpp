#include "dataset.h"

DataSet::DataSet(std::string name, std::vector<std::vector<double>> entries, vector<int> classes) : name(name), entries(entries), classes(classes) {

}

std::string DataSet::getName() {
    return name;
}

vector<vector<double>> DataSet::getEntries() {
    return entries;
}

double DataSet::findMax(unsigned int i) {
    double max = 0.0;

    if (i < this->entries[0].size()) {
        max = this->entries[0][i];
        for (unsigned int j = 1; j < this->entries.size(); ++j) {
            if (max < this->entries[j][i]) {
                max = this->entries[j][i];
            }
        }
    }

    return max;
}

double DataSet::findMin(unsigned int i) {
    double min = 0.0;

    if (i < this->entries[0].size()) {
        min = this->entries[0][i];
        for (unsigned int j = 1; j < this->entries.size(); ++j) {
            if (min > this->entries[j][i]) {
                min = this->entries[j][i];
            }
        }
    }

    return min;
}

QVector<double> DataSet::getXValues(unsigned int i) {
    QVector<double> xi = QVector<double>();

    for (unsigned int j = 0; j < entries.size(); ++j) {
        xi.append(entries[j][i]);
    }

    return xi;
}

vector<int> DataSet::getDataClasses() {
    return this->classes;
}
