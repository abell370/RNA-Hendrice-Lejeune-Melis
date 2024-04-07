#include "maincontroller.h"
#include "csvreader.h"
#include "layer.h"
#include "activationfunction.h".
#include "sigmoidactivation.h"

MainController::MainController(vector<string> pathToDataSets, vector<string> learningModelsList) : pathToDataSets(pathToDataSets), learningModelsList(learningModelsList) {};

/*
QVector<double> MainController::calcGraph(uint iterationIndex, std::vector<double> x1){
    return learningModel->calcGraph(iterationIndex, x1);
}
*/


void MainController::setupModel(int modelIndex, string pathToData, double learningRate, int nbClass, bool deeplearning)
{
    CSVReader reader("data/" + pathToData);
    if (reader.readCSV())
    {
        vector<vector<double>> data = reader.getData();
        // Sert à ajouter le x0 aux données => TODO aller modofier les algos pour ne pas devoir modifier les données de bases
        if (pathToData == "table_3_1.csv") reverse(data.begin(), data.end());
        if (deeplearning)
        {

        }
        else
        {
            // TODO heritage a ameliorer....
            Layer* layer = new Layer();
            layer->setup(data, nbClass, modelIndex, learningRate);
            this->model = layer;
        }
    }
}

void MainController::startTraining(int maxIter, double errorThreshold, int maxClassificationError, int activationFct)
{
    // TODO  ceation dans une classe separee
    ActivationFunction* aFunction = new SigmoidActivation();
    if (activationFct == 0)
    {
        aFunction = new IdentityActivation();
    }
    this->model->train(errorThreshold, maxIter, aFunction, maxClassificationError);
    this->model->getResult(); // debug pour voir le résultat   
}

void MainController::reset() {
    this->model->reset();
}


vector<string> MainController::getLearningModels() 
{
    return learningModelsList;
}

vector<string> MainController::getDataSets() 
{
    return pathToDataSets;
}

DataSet MainController::getDataSet(int ds) {
    return dataSets[ds];
}

/*
Iteration MainController::getIteration(uint iter){
    LearningModel *currentLM = learningModel;
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
}

*/
