#pragma once
#include "activationfunction.h"
#include <vector>

using namespace std;

class LayeringModel
{
public:
	virtual void train(double stopThreadshold, int maxEpoc, ActivationFunction* aFunction, int maxClassificationError) {};
	virtual void getResult() {};
	virtual void reset() {};
};

