#pragma once
#include "activationfunction.h"
class IdentityActivation :
    public ActivationFunction
{
public:
    IdentityActivation() {};
    ~IdentityActivation() {};

    double compute(double entry) const;
};

