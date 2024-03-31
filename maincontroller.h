#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <vector>
#include "dataset.h"
#include "iteration.h"
#include "layer.h"
#include "identityactivation.h"

using namespace std;

class MainController
{
private:
    vector<string> pathToDataSets, learningModelsList;
    vector<DataSet> dataSets;
    Layer* neurons;

public:
    MainController(vector<string> pathToDataSets, vector<string> learningModelsList);

    void startLearning(int modelIndex, string pathToData, double learningRate, int maxIter, double errorThreshold, int nbClass, int nbEntry);
    QVector<double> calcGraph(uint iterationIndex, std::vector<double> x1);
    void reset();

    
    vector<string> getLearningModels();
    vector<string> getDataSets();
    DataSet getDataSet(int ds);


    /*
    Iteration getIteration(uint iter);
    bool hasIterations();
    unsigned int iterationsSize();
    */
};

#endif // MAINCONTROLLER_H
