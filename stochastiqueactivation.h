#pragma once
#include "activationfunction.h"
class StochastiqueActivation :
    public ActivationFunction
{
public:
    StochastiqueActivation() {};
    ~StochastiqueActivation() {};

    double compute(double entry) const;
};

