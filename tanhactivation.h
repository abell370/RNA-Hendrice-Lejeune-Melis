#pragma once
#include "activationfunction.h"
class TanHActivation :
    public ActivationFunction
{
public:
    TanHActivation() {};
    ~TanHActivation() {};

    double compute(double entry) const;
    double performThresholding(double entry) const;
};

