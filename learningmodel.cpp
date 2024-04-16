#include "learningmodel.h"

LearningModel::LearningModel(vector<vector<double>> dataset, ActivationFunction* activation, vector<double> weights, double learningRate)
{
    this->dataset = dataset;
    this->activation = activation;
    this->n = learningRate;
    this->weights = weights;
    this->result = 0.;
}

std::vector<Iteration> LearningModel::getIterations() {
    return std::vector<Iteration>(this->iterations);
}

std::string LearningModel::getName() {
    return "LearningModel";
}

vector<double> LearningModel::getWeights() {
    return this->weights;
}

void LearningModel::addIteration(Iteration iteration) {
    iterationsSaved.push_back(iteration);
}

void LearningModel::reset() {
    iterationsSaved.clear();
}

