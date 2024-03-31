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
    void learn(int maxIter, double minMeanQuadraticError, int indexOfPredictedData, ActivationFunction* activation);
    string getResult() override;
    std::string getName() {
        return "Adaline Perceptron";
    };

private:
    int nbErreurs = 0, x0 = 1, iterations = 0;
    double n;
    vector<double> weights, result;
    vector<vector<double>> data; // avec entrée fictive x0 ([x0,x1,x2,d])

    double executeOneIteration(int indexOfPredictedData, ActivationFunction* activation);
    double calculMeanQuadratic(int indexOfPredictedData);
};

