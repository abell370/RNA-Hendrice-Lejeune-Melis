#pragma once
#include "activationfunction.h"
/*
    Fonction d'activation Identit�/Lin�aire
*/
class IdentityActivation :
    public ActivationFunction
{
public:
    IdentityActivation() {};
    ~IdentityActivation() {};

    double compute(double entry) const;
    double performThresholding(double entry) const;
};

