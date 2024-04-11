#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <vector>
#include "dataset.h"
#include "iteration.h"
#include "layer.h"
#include "identityactivation.h"
#include "layeringmodel.h"

using namespace std;

class MainController
{
private:
    vector<string> pathToDataSets, learningModelsList, pathToValidationDatasets;
    LayeringModel* model;

public:
    MainController(vector<string> pathToDataSets, vector<string> pathToValidationDatasets, vector<string> learningModelsList);

    void setupModel(int modelIndex, string pathToData, double learningRate, int nbClass, bool deeplearning, int hiddenLayerSize, int activationFct);
    void startTraining(int maxIter, double errorThreshold, int maxClassificationError);
    map<string, double> checkModelAccuracy(string pathToData);
    QVector<double> calcGraph(uint iterationIndex, std::vector<double> x1);
    void reset();


    vector<string> getLearningModels();
    vector<string> getDataSets();
    vector<string> getValidationDatasets();


    /*
    Iteration getIteration(uint iter);
    bool hasIterations();
    unsigned int iterationsSize();
    */
};

#endif // MAINCONTROLLER_H
