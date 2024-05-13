#include "maincontroller.h"
#include "csvreader.h"
#include "monolayer.h"
#include "activationfunction.h"
#include "sigmoidactivation.h"
#include "multilayer.h"
#include "tanhactivation.h"

MainController::MainController(vector<string> pathToDataSets, vector<string> pathToValidationDatasets, vector<string> learningModelsList, DataSetReader* dataSetReader) : pathToDataSets(pathToDataSets), pathToValidationDatasets(pathToValidationDatasets), learningModelsList(learningModelsList), dataSetReader(dataSetReader) {};


void MainController::setupModel(int modelIndex, string pathToData, double learningRate, int nbClass, bool deeplearning, int hiddenLayerSize, vector<int> activationFct, bool randomNormalWeights)
{
    string datapath = "data/" + pathToData;

    // delete previous DataSet object
    this->data = this->dataSetReader->read(datapath, nbClass);
     
    if (data != NULL)
    {
        vector<ActivationFunction*> aFunctions = {};

        for (int i: activationFct)
        {
            switch (i) {
            case 0:
                aFunctions.push_back(new IdentityActivation());
                break;
            case 1:
                aFunctions.push_back(new SimpleActivation());
                break;
            case 2:
                aFunctions.push_back(new TanHActivation());
                break;
            default:
                aFunctions.push_back(new SigmoidActivation());
                break;
            }
        }

        // Sert à ajouter le x0 aux données => TODO aller modofier les algos pour ne pas devoir modifier les données de bases
        //if (pathToData == "table_3_1.csv") reverse(data->getEntries().begin(), data->getEntries().end());
        if (deeplearning)
        {
            MultiLayer* layeringmodel = new MultiLayer(data->getEntries(), aFunctions);
            layeringmodel->setup(hiddenLayerSize,nbClass, learningRate);
            this->model = layeringmodel;
        }
        else
        {
            MonoLayer* layer = new MonoLayer(data->getEntries(), aFunctions);
            layer->setup(nbClass, modelIndex, learningRate, randomNormalWeights);
            this->model = layer;
        }
    }
}

History* MainController::startTraining(int maxIter, double errorThreshold, int maxClassificationError)
{
    this->history = model->train(errorThreshold, maxIter, maxClassificationError);
    return this->history;
}

map<string, double> MainController::checkModelAccuracy(string pathToData)
{
    map<string, double> result;
    CSVReader reader("data/validation/" + pathToData);
    if (reader.readCSV())
    {
        vector<vector<double>> data = reader.getData();
        result = this->model->checkAccuracy(data);
    }
    return result;
}

void MainController::reset() {
    this->model->reset();
}

vector<string> MainController::getValidationDatasets()
{
    return pathToValidationDatasets;
}

vector<string> MainController::getLearningModels() 
{
    return learningModelsList;
}

vector<string> MainController::getDataSets() 
{
    return pathToDataSets;
}

vector<vector<double>> MainController::getData() {
    return data->getEntries();
}

DataSet* MainController::getDataSet() {
    return data;
}

vector<vector<double>> MainController::getDecisionWeights(int epoc) {
    if (0 <= epoc && epoc < history->getHistory().size()) {
        return this->history->getWeights(epoc);
    }
    else {
        return { {} };
    }
}

unsigned int MainController::getIterationCount() {
    return this->history->getIterationCount();
}

vector<double> MainController::getLoss() {
    return this->history->getMSEEvolution();
}