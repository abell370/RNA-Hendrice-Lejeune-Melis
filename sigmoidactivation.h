#pragma once
#include "activationfunction.h"

/*
    Fonction d'activation Sigmo�d
*/
class SigmoidActivation :
    public ActivationFunction
{
public:
    SigmoidActivation() {};
    ~SigmoidActivation() {};

    double compute(double entry) const;
    double performThresholding(double entry) const;

};

