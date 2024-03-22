#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <vector>
#include "dataset.h"
#include "iteration.h"
#include "layer.h"

using namespace std;

class MainController
{
private:
    vector<DataSet> dataSets;
    Layer* neurons;

public:
    MainController(std::vector<DataSet> dataSets);

    void startLearning(string learningModelName, string pathToData, double learningRate, int maxIter, double errorThreshold);
    QVector<double> calcGraph(uint iterationIndex, std::vector<double> x1);
    void reset();

    QList<QString> getLearningModels();
    QList<QString> getDataSets();
    DataSet getDataSet(uint ds);
    Iteration getIteration(uint iter);
    bool hasIterations();
    unsigned int iterationsSize();
};

#endif // MAINCONTROLLER_H
