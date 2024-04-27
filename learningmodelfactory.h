#ifndef LEARNINGMODELFACTORY_H
#define LEARNINGMODELFACTORY_H

#include "learningmodel.h"
#include "adalineperceptron.h"
#include "gradientPerceptron.h"
#include "simpleperceptron.h"

class LearningModelFactory
{
public:
    ~LearningModelFactory() {};

    static LearningModel* create(int modelIndex, vector<vector<double>> dataset, vector<double> weights, double learningRate, ActivationFunction* aFunction)
    {
        if (modelIndex == 0)
        {
            return new AdalinePerceptron(dataset, aFunction, weights, learningRate);
        }
        else if (modelIndex == 1)
        {
            return new GradientPerceptron(dataset, aFunction, weights, learningRate);
        }
        else if (modelIndex == 2)
        {
            return new SimplePerceptron(dataset, aFunction, weights, learningRate);
        }
    }
};

#endif // LEARNINGMODELFACTORY_H
