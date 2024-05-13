#pragma once
#include "learningmodel.h"
#include <vector>

using namespace std;
/*
    Implémentation de Adaline
*/
class AdalinePerceptron : public LearningModel
{
public:
    using LearningModel::LearningModel;

    map<string, double> checkAccuracy(int tagIndex);
    std::string getName() {
        return "Adaline Perceptron";
    };

private:
    double executeOneIteration(int indexOfPredictedData, bool updateWeights);
    double calculMeanQuadratic(int indexOfPredictedData);
};

