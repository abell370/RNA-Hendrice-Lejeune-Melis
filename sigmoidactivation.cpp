#include "sigmoidactivation.h"
#include <cmath>

double SigmoidActivation::compute(double entry) const
{
	return 1 / (1 + std::exp(-entry));
}

double SigmoidActivation::performThresholding(double entry) const
{
	return entry >= 0.5 ? 1. : 0.;
}