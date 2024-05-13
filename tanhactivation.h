#pragma once
#include "activationfunction.h"
/*
    Fonction d'activation tangente hyperbolique
*/
class TanHActivation :
    public ActivationFunction
{
public:
    TanHActivation() {};
    ~TanHActivation() {};

    double compute(double entry) const;
    double performThresholding(double entry) const;
};

