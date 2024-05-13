#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <vector>
#include "dataset.h"
#include "iteration.h"
#include "monolayer.h"
#include "identityactivation.h"
#include "simpleactivation.h"
#include "layeringmodel.h"
#include "DataSetReader.h"

using namespace std;

/*
    Classe permettant de faire de lien entre la vue et le modèle (implémentation d'un MVC)
*/
class MainController
{
private:
    vector<string> pathToDataSets, learningModelsList, pathToValidationDatasets;
    LayeringModel* model;
    DataSet* data;
    DataSetReader* dataSetReader;
    History* history;

public:
    MainController(vector<string> pathToDataSets, vector<string> pathToValidationDatasets, vector<string> learningModelsList, DataSetReader* dataSetReader);

    void setupModel(int modelIndex, string pathToData, double learningRate, int nbClass, bool deeplearning, int hiddenLayerSize, vector<int> activationFct, bool randomNormalWeights);
    History* startTraining(int maxIter, double errorThreshold, int maxClassificationError);
    map<string, double> checkModelAccuracy(string pathToData);
    QVector<double> calcGraph(uint iterationIndex, std::vector<double> x1);
    void reset();

    vector<string> getLearningModels();
    vector<string> getDataSets();
    vector<string> getValidationDatasets();
    vector<vector<double>> getData();
    DataSet* getDataSet();
    vector<vector<double>> getDecisionWeights(int epoc);
    vector<double> getLoss();
    unsigned int getIterationCount();


    /*
    Iteration getIteration(uint iter);
    bool hasIterations();
    unsigned int iterationsSize();*/
};

#endif // MAINCONTROLLER_H
