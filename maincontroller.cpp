#include "maincontroller.h"
#include "layer.h"

MainController::MainController(std::vector<DataSet> dataSets) : dataSets(dataSets) {
}

/*
QVector<double> MainController::calcGraph(uint iterationIndex, std::vector<double> x1){
    return learningModel->calcGraph(iterationIndex, x1);
}
*/


void MainController::startLearning(string learningModelName, string pathToData, double learningRate, int maxIter, double errorThreshold)
{
    vector<vector<double>> data;
    this->neurons = new Layer(data, learningModelName, 1, learningRate);
    this->neurons->learn(maxIter, errorThreshold == 0.0 ? NULL : errorThreshold);
}

void MainController::reset() {
    this->neurons->reset();
}


QList<QString> MainController::getLearningModels() {
    QList<QString> lmNames = { "Adaline", "Gradient", "Simple" };
    return lmNames;
}

QList<QString> MainController::getDataSets() {
    QList<QString> dsNames;
    dsNames.reserve(this->dataSets.size());
    for (uint i = 0; i < this->dataSets.size(); i++) {
        dsNames.push_back(QString::fromStdString(this->dataSets[i].getName()));
    }
    return dsNames;
}

DataSet MainController::getDataSet(uint ds) {
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
