#pragma once
#include "activationfunction.h"
#include <vector>
#include <map>
#include <string>

using namespace std;

class LayeringModel
{
public:

	LayeringModel(vector<vector<double>> dataset, ActivationFunction* activation);

	virtual void train(double stopThreadshold, int maxEpoc, int maxClassificationError) = 0;
	virtual vector<double> getResult() = 0;
	virtual map<string, double> checkAccuracy(vector<vector<double>> validationDataset) = 0;
	virtual void reset() = 0;
	virtual vector<vector<double>> getDecisionWeights() = 0;

protected:
	vector<vector<double>> dataset;
	vector<double> eMoyDuringTraining;
	ActivationFunction* aFunction;
};

