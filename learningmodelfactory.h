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

    static LearningModel* create(int modelIndex)
    {
        if (modelIndex == 0)
        {
            return new AdalinePerceptron();
        }
        else if (modelIndex == 1)
        {
            return new GradientPerceptron();

        }
    }
};

#endif // LEARNINGMODELFACTORY_H
