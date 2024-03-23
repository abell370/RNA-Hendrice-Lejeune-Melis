#include "maincontroller.h"
#include "csvreader.h"
#include "layer.h"

MainController::MainController(vector<string> pathToDataSets, vector<string> learningModelsList) : pathToDataSets(pathToDataSets), learningModelsList(learningModelsList) {};

/*
QVector<double> MainController::calcGraph(uint iterationIndex, std::vector<double> x1){
    return learningModel->calcGraph(iterationIndex, x1);
}
*/


void MainController::startLearning(int modelIndex, string pathToData, double learningRate, int maxIter, double errorThreshold)
{
    CSVReader reader("data/"+pathToData);
    if (reader.readCSV())
    {
        vector<vector<double>> data = reader.getData();
        // Sert à ajouter le x0 aux données => TODO aller modofier les algos pour ne pas devoir modifier les données de bases
        for (auto& point : data) {
            point.insert(point.begin(), 1);
        }
        this->neurons = new Layer(data, modelIndex, 1, learningRate);
        this->neurons->learn(maxIter, errorThreshold == 0.0 ? NULL : errorThreshold);
    }
   
}

void MainController::reset() {
    this->neurons->reset();
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
