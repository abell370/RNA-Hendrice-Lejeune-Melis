#pragma once
#include <vector>
#include "learningmodel.h"

using namespace std;

class GradientPerceptron : public LearningModel
{
public:

    using LearningModel::LearningModel;

    void learn(int maxIter, double minMeanQuadraticError, int indexOfPredictedData, int maxClassificationError);
    map<string, double> checkAccuracy(int tagIndex);
    string getResult();
    std::string getName() {
        return "Gradient Perceptron";
    };

private:
    double executeOneIteration(int indexOfPredicted, bool updateWeights);
    double calculMeanQuadratic(int indexOfPredictedData);
};

