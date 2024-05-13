#ifndef SIMPLEPERCEPTRON_H
#define SIMPLEPERCEPTRON_H

#include "learningmodel.h"

using namespace std;

/*
    Implémentation du Perceptron simple
*/
class SimplePerceptron : 
    public LearningModel
{
public:
    using LearningModel::LearningModel;

    void learn(int maxIter, double minMeanQuadraticError, int indexOfPredictedData, int maxClassificationError) override;
    map<string, double> checkAccuracy(int tagIndex);
    std::string getName() {
        return "Simple Perceptron";
    };
private:
    double executeOneIteration(int indexOfPredicted, bool updateWeight);
    bool isBinary();
};

#endif // SIMPLEPERCEPTRON_H
