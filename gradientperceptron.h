#pragma once
#include <vector>
#include "learningmodel.h"

using namespace std;

/*
    Impl�mentation de la Descente de Gradient
*/
class GradientPerceptron : public LearningModel
{
public:

    using LearningModel::LearningModel;

    map<string, double> checkAccuracy(int tagIndex);
    std::string getName() {
        return "Gradient Perceptron";
    };

private:
    double executeOneIteration(int indexOfPredicted, bool updateWeights);
    double calculMeanQuadratic(int indexOfPredictedData);
};

