#include "learningmodel.h"

std::vector<Iteration> LearningModel::getIterations() {
    return std::vector<Iteration>(this->iterations);
}

std::string LearningModel::getName() {
    return "LearningModel";
}

void LearningModel::addIteration(Iteration iteration) {
    this->iterations.push_back(iteration);
}

void LearningModel::reset() {
    this->iterations.clear();
}

