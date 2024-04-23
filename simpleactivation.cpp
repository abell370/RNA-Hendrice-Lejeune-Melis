#include "simpleactivation.h"
#include <cmath>

double SimpleActivation::compute(double entry) const
{
	return entry >= 0. ? 1. : 0.;
}

double SimpleActivation::performThresholding(double entry) const
{
	return entry;
}