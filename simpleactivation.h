#pragma once
#include "activationfunction.h"
class SimpleActivation :
    public ActivationFunction
{
public:
    SimpleActivation() {};
    ~SimpleActivation() {};

    double compute(double entry) const;
    double performThresholding(double entry) const;

};
