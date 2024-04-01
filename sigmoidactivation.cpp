#include "sigmoidactivation.h"
#include <cmath>

double SigmoidActivation::compute(double entry) const
{
	return 1 / (1 + std::exp(-entry));
}
