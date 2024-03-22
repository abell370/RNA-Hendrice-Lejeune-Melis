#ifndef DATASET_H
#define DATASET_H

#include <vector>
#include <QVector>

using namespace std;

class DataSet {
private:
    string name;
    vector<vector<double>> entries;
public:
    DataSet(string name, vector<vector<double>> entries);

    string getName();
    vector<vector<double>> getEntries();

    //find min/max value of xi
    double findMin(unsigned int i);
    double findMax(unsigned int i);
    QVector<double> getXValues(unsigned int i);
};



#endif // DATASET_H
