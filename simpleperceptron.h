#ifndef SIMPLEPERCEPTRON_H
#define SIMPLEPERCEPTRON_H

#include "learningmodel.h"

using namespace std;

class SimplePerceptron : 
    public LearningModel
{
private:

    void loopWhileErrorNotNull(int indexOfPredicted);
    int executeOneIteration(int indexOfPredicted, bool updateWeights);

public:
    using LearningModel::LearningModel;

    void learn(int maxIter, double minMeanQuadraticError, int indexOfPredictedData, int maxClassificationError);
    map<string, double> checkAccuracy(int tagIndex);
    string getResult();
    std::string getName() {
        return "Simple Perceptron";
    };

private:
    double executeOneIteration(int indexOfPredictedData, bool updateWeights);
    double calculMeanQuadratic(int indexOfPredictedData);
};

#endif // SIMPLEPERCEPTRON_H
