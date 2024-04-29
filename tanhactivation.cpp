#include "tanhactivation.h"
#include <cmath>

double TanHActivation::compute(double entry) const
{
	return 2 / (1 + std::exp(-2*entry)) - 1;
}

double TanHActivation::performThresholding(double entry) const
{
	return entry >= 0. ? 1. : -1.;
}