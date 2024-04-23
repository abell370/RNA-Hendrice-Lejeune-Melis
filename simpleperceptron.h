#ifndef SIMPLEPERCEPTRON_H
#define SIMPLEPERCEPTRON_H

#include "learningmodel.h"

using namespace std;

class SimplePerceptron : 
    public LearningModel
{
public:
    using LearningModel::LearningModel;

    map<string, double> checkAccuracy(int tagIndex);
    string getResult() override;
    std::string getName() {
        return "Simple Perceptron";
    };

private:
    double executeOneIteration(int indexOfPredictedData, bool updateWeights);
    double calculMeanQuadratic(int indexOfPredictedData);
};

#endif // SIMPLEPERCEPTRON_H
