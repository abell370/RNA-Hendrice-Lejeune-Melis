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

    static LearningModel* create(string className)
    {
        if (className == "Adaline")
        {
            return new AdalinePerceptron();
        }
        else if (className == "Gradient")
        {
            return new GradientPerceptron();
        }
        else
        {
            return new SimplePerceptron();
        }
    }
};

#endif // LEARNINGMODELFACTORY_H
