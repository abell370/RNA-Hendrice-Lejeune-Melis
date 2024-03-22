#pragma once
#include <vector>
#include "learningmodel.h"

using namespace std;

class GradientPerceptron : public LearningModel
{
public:
    GradientPerceptron();
    ~GradientPerceptron() {};

    void loopOnIterations(float minErrorAccepted, int maxEpoc);
    void loopWhileErrorNotNull(int maxEpoc);

    void setup(vector<vector<double>> dataset, vector<double> weights, double learningRate);
    void learn(int maxIter, double minMeanQuadraticError, int indexOfPredictedData);
    QVector<double> calcGraph(uint iterationIndex, std::vector<double> x1);
    std::string getName() {
        return "Adaline Perceptron";
    };

private:
    int nbErreurs = 0, x0 = 1, iterations = 0;
    double n;
    vector<double> weights;
    vector<vector<double>> data; // avec entr e fictive x0 ([x0,x1,x2,d])

    double executeOneIteration();
};

