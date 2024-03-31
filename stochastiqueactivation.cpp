#include "stochastiqueactivation.h"
#include <cmath>

double StochastiqueActivation::compute(double entry) const
{
	return 1 / (1 + std::exp(-entry));
}
