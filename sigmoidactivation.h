#pragma once
#include "activationfunction.h"
class SigmoidActivation :
    public ActivationFunction
{
public:
    SigmoidActivation() {};
    ~SigmoidActivation() {};

    double compute(double entry) const;
    double performThresholding(double entry) const;

};

