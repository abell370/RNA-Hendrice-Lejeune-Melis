#pragma once
#include <vector>
#include "activationfunction.h"
using namespace std;

class DeepLearning
{
public:
	DeepLearning(vector<vector<double>> dataset);
	~DeepLearning() {};

	void setup(int hiddenLayerSize, int outputLayerSize, int nbTags, double learningRate);
	void learn(double stopThreadshold, int maxEpoc, ActivationFunction* aFunction);

private:
	int amountOfHiddenNeuron, amountOfNeuron, nbTags;
	vector<vector<double>> dataset, weightsHidden, weightsOutput;
	double learningRate;

	double executeOneEpoc(double stopThreadshold, ActivationFunction* aFunction);

	vector<double> calculatePotentials(vector<double> outputs, int amountOfNeuron, vector<vector<double>> weights);
	vector<double> calculateOutputs(vector<double> example, int amountOfNeuron, ActivationFunction* aFunction);

	double calculateEMeanQuad(vector<double> example, vector<double> outputs, int nbTags);

	vector<double> caclulateOutputSigError(vector<double> example, vector<double> zOutputs, int nbTags, int amountOfNeuron);
	vector<double> caclulateHiddenSigError(vector<double> hiddenLayerOutputs, int amountOfNeuron);

	vector<double> cumulHiddenLayerSigError(vector<double> hiddenOutputSigError, vector<double> outputSigError, int amountOfNeuron, int amountOfHiddenNeuron);

	void editWeights(vector<double> sigError, vector<double> example, vector<vector<double>> weights);
};

