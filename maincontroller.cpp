#include "maincontroller.h"
#include "csvreader.h"
#include "layer.h"
#include "activationfunction.h".
#include "sigmoidactivation.h"
#include "deeplearning.h"

MainController::MainController(vector<string> pathToDataSets, vector<string> pathToValidationDatasets, vector<string> learningModelsList) : pathToDataSets(pathToDataSets), pathToValidationDatasets(pathToValidationDatasets), learningModelsList(learningModelsList) {};

/*
QVector<double> MainController::calcGraph(uint iterationIndex, std::vector<double> x1){
    return learningModel->calcGraph(iterationIndex, x1);
}
*/


void MainController::setupModel(int modelIndex, string pathToData, double learningRate, int nbClass, bool deeplearning, int hiddenLayerSize, int activationFct, bool randomNormalWeights)
{
    CSVReader reader("data/" + pathToData);
    if (reader.readCSV())
    {

        // TODO  ceation dans une classe separee
        ActivationFunction* aFunction = new SigmoidActivation();
        if (activationFct == 0)
        {
            aFunction = new IdentityActivation();
        }

        this->data = reader.getData();
        // Sert à ajouter le x0 aux données => TODO aller modofier les algos pour ne pas devoir modifier les données de bases
        if (pathToData == "table_3_1.csv") reverse(data.begin(), data.end());
        if (deeplearning)
        {
            MultiLayer* layeringmodel = new MultiLayer(data, aFunction);
            layeringmodel->setup(hiddenLayerSize,nbClass, learningRate);
            this->model = layeringmodel;
        }
        else
        {
            // TODO heritage a ameliorer....
            MonoLayer* layer = new MonoLayer(data, aFunction);
            layer->setup(nbClass, modelIndex, learningRate, randomNormalWeights);
            this->model = layer;
        }
    }
}

void MainController::startTraining(int maxIter, double errorThreshold, int maxClassificationError)
{
    this->model->train(errorThreshold, maxIter, maxClassificationError);
    this->model->getResult(); // debug pour voir le résultat   
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
    return data;
}

vector<vector<double>> MainController::getDecisionWeights() {
    return model->getDecisionWeights();
}


/*Iteration MainController::getIteration(uint iter) {
    LayeringModel *layeringModel = this->model;
    if(currentLM != nullptr && iter < currentLM->getIterations().size()){
        return currentLM->getIterations()[iter];
    }
    return Iteration();
}

bool MainController::hasIterations(){
    return !learningModel->getIterations().empty();
}

unsigned int MainController::iterationsSize(uint lm){
    return learningModel->getIterations().size();
}*/
