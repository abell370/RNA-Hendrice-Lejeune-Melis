#pragma once
#include <vector>
#include "activationfunction.h"
using namespace std;

class DeepLearning
{
public:
	DeepLearning(vector<vector<double>> dataset, vector<vector<double>> weightsHidden, vector<vector<double>> weightsOutput, double learningRate);
	~DeepLearning() {};

	void learn(int hiddenLayerSize, int outputLayerSize, double stopThreadshold, int nbTags, ActivationFunction* aFunction);

private:
	vector<vector<double>> dataset, weightsHidden, weightsOutput;
	double learningRate;

	vector<double> calculateHiddenLayerPotentials(vector<double> example, int amountOfHiddenNeuron);
	vector<double> calculateHiddenLayerOutputs(vector<double> example, int amountOfHiddenNeuron, ActivationFunction* aFunction);

	vector<double> calculatePotentials(vector<double> hLayerOutputs, int amountOfNeuron);
	vector<double> calculateOutputs(vector<double> example, int amountOfHiddenNeuron, ActivationFunction* aFunction);

	double calculateEMeanQuad(vector<double> example, vector<double> outputs, int nbTags);

	vector<double> caclulateOutputSigError(vector<double> example, vector<double> zOutputs, int nbTags, int amountOfNeuron);
	vector<double> caclulateHiddenSigError(vector<double> hiddenLayerOutputs, int amountOfNeuron);

	vector<double> cumulHiddenLayerSigError(vector<double> hiddenOutputSigError, vector<double> outputSigError, int amountOfNeuron);

	void editNeuronWeights(vector<double> outputSigError, vector<double> y);
	void editHiddenNeuronWeights(vector<double> cumulHiddenLayerSigError, vector<double> example, int amountOfHiddenNeuron);
};

