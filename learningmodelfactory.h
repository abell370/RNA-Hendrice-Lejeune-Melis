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
            return nullptr;
        }
        else if (modelIndex == 1)
        {
            return nullptr;

        }
    }
};

#endif // LEARNINGMODELFACTORY_H
