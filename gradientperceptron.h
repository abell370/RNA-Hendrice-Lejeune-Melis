#pragma once
#include <vector>
#include "learningmodel.h"

using namespace std;

class GradientPerceptron : public LearningModel
{
public:

    GradientPerceptron();
    ~GradientPerceptron();

    void setup(vector<vector<double>> dataset, vector<double> weights, double learningRate);
    void learn(int maxIter, double minMeanQuadraticError, int indexOfPredictedData, ActivationFunction* activation);
    string getResult();
    std::string getName() {
        return "Gradient Perceptron";
    };

private:
    int nbErreurs = 0, x0 = 1, iterations = 0;
    double n;
    vector<double> weights, result;
    vector<vector<double>> data; // avec entr e fictive x0 ([x0,x1,x2,d])

    double executeOneIteration(int indexOfPredicted, ActivationFunction* activation);
    double calculMeanQuadratic(int indexOfPredictedData);
};

