#ifndef SIMPLEPERCEPTRON_H
#define SIMPLEPERCEPTRON_H

#include "learningmodel.h"

using namespace std;

class SimplePerceptron : 
    public LearningModel
{
public:
    using LearningModel::LearningModel;

    void learn(int maxIter, double minMeanQuadraticError, int indexOfPredictedData, int maxClassificationError);
    map<string, double> checkAccuracy(int tagIndex);
    string getResult();
    std::string getName() {
        return "Simple Perceptron";
    };
private:

    void loopWhileErrorNotNull(int indexOfPredicted);
    double executeOneIteration(int indexOfPredicted, bool updateWeight);
};

#endif // SIMPLEPERCEPTRON_H
