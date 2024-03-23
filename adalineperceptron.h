#pragma once
#include "learningmodel.h"
#include <vector>

using namespace std;

class AdalinePerceptron : public LearningModel
{
public:
    AdalinePerceptron();
    ~AdalinePerceptron() {};

    void setup(vector<vector<double>> dataset, vector<double> weights, double learningRate);
    void learn(int maxIter, double minMeanQuadraticError, int indexOfPredictedData);
    std::string getName() {
        return "Adaline Perceptron";
    };

private:
    int nbErreurs = 0, x0 = 1, iterations = 0;
    double n;
    vector<double> weights;
    vector<vector<double>> data; // avec entrée fictive x0 ([x0,x1,x2,d])

    void loopOnIterations(float minErrorAccepted, int maxEpoc, int indexOfPredictedData);
    void loopWhileErrorNotNull(int maxEpoc, int indexOfPredictedData);
    double executeOneIteration(int indexOfPredictedData);
    double calculMeanQuadratic(int indexOfPredictedData);
};

