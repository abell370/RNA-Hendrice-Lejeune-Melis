#pragma once
#include "learningmodel.h"
#include <vector>

using namespace std;

class AdalinePerceptron : public LearningModel
{
public:
    using LearningModel::LearningModel;

    void learn(int maxIter, double minMeanQuadraticError, int indexOfPredictedData, int maxClassificationError);
    map<string, double> checkAccuracy(int tagIndex);
    string getResult() override;
    std::string getName() {
        return "Adaline Perceptron";
    };

private:
    double executeOneIteration(int indexOfPredictedData, bool updateWeights);
    double calculMeanQuadratic(int indexOfPredictedData);
};

