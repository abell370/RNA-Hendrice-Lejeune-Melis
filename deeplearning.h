#pragma once
#include <vector>
#include "activationfunction.h"
#include "layeringmodel.h"
#include "history.h"

using namespace std;

class MultiLayer : 
	public LayeringModel
{
public:
	
	using LayeringModel::LayeringModel;

	void setup(int hiddenLayerSize, int nbTags, double learningRate);
	History* train(double stopThreadshold, int maxEpoc, int maxClassificationError);
	map<string, double> checkAccuracy(vector<vector<double>> validationDataset);
	void reset();

	vector<vector<double>> getDecisionWeights();

private:
	int amountOfHiddenNeuron = 0, nbTags = 0, classificationErrors = 0, nbEpoc = 0;
	vector<vector<double>> weightsHidden, weightsOutput;
	double learningRate = 0.;

	double executeOneEpoc(double stopThreadshold, bool updateWeights);

	vector<double> calculatePotentials(vector<double> outputs, int amountOfNeuron, vector<vector<double>> *weights);
	vector<double> calculateOutputs(vector<double> example, int amountOfNeuron);

	double calculateEQuad(const vector<vector<double>>& outputs);

	vector<double> caclulateOutputSigError(vector<double> example, vector<double> zOutputs, int nbTags, int amountOfNeuron);
	vector<double> caclulateHiddenSigError(vector<double> hiddenLayerOutputs, int amountOfNeuron);

	vector<double> cumulHiddenLayerSigError(vector<double> hiddenOutputSigError, vector<double> outputSigError, int amountOfNeuron, int amountOfHiddenNeuron);

	void editWeights(vector<double> sigError, vector<double> example, vector<vector<double>> *weights);
	void shuffleDataset();
};

