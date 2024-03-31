#ifndef SIMPLEPERCEPTRON_H
#define SIMPLEPERCEPTRON_H

#include "learningmodel.h"

using namespace std;

class SimplePerceptron : public LearningModel
{
private:
    int nbErreurs = 0, x0 = 1, iterations = 0;
    double n;
    vector<double> weights;
    vector<vector<double>> data; // avec entr e fictive x0 ([x0,x1,x2,d])

    void loopOnIterations(float minErrorAccepted, int maxEpoc, int indexOfPredictedData);
    void loopWhileErrorNotNull(int maxEpoc, int indexOfPredictedData);
    double executeOneIteration(int indexOfPredictedData);

public:
    SimplePerceptron() {};
    ~SimplePerceptron() {};

    void setup(vector<vector<double>> dataset, vector<double> weights, double learningRate);
    void learn(int maxIter, double minMeanQuadraticError, int indexOfPredictedData, ActivationFunction* activation);
    string getResult();
    std::string getName() {
        return "Simple Perceptron";
    };
};

#endif // SIMPLEPERCEPTRON_H
