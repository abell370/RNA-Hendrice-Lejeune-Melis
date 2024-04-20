#ifndef DATASET_H
#define DATASET_H

#include <vector>
#include <QVector>
#include <string>

using namespace std;

class DataSet {
private:
    string name;
    vector<vector<double>> entries;
    vector<int> classes;
public:
    DataSet(string name, vector<vector<double>> entries, vector<int> classes);

    string getName();
    vector<vector<double>> getEntries();
    vector<int> getDataClasses();

    //find min/max value of xi
    double findMin(unsigned int i);
    double findMax(unsigned int i);
    QVector<double> getXValues(unsigned int i);
};



#endif // DATASET_H
