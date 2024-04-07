#include "identityactivation.h"

double IdentityActivation::compute(double entry) const
{
	// y = potential
	return entry;
}

double IdentityActivation::performThresholding(double entry) const
{
	return entry >= 0. ? 1. : -1.;
}