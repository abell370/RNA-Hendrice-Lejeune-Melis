#ifndef SIMPLEPERCEPTRON_H
#define SIMPLEPERCEPTRON_H

#include "learningmodel.h"

using namespace std;

class SimplePerceptron : public LearningModel
{
private:

    void loopOnIterations(float minErrorAccepted, int maxEpoc, int indexOfPredictedData);
    void loopWhileErrorNotNull(int maxEpoc, int indexOfPredictedData);
    double executeOneIteration(int indexOfPredictedData);

public:
    
    using LearningModel::LearningModel;

    void learn(int maxIter, double minMeanQuadraticError, int indexOfPredictedData, int maxClassificationError);
    map<string, double> checkAccuracy() {};
    string getResult();
    std::string getName() {
        return "Simple Perceptron";
    };
};

#endif // SIMPLEPERCEPTRON_H
