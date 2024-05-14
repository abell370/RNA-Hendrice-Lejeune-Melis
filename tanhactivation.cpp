#include "tanhactivation.h"
#include <cmath>

double TanHActivation::compute(double entry) const
{
	return std::exp(entry) - std::exp(-entry) / std::exp(entry) + std::exp(-entry);
}

double TanHActivation::performThresholding(double entry) const
{
	return entry >= 0. ? 1. : -1.;
}