#include "deeplearning.h"

DeepLearning::DeepLearning(vector<vector<double>> dataset)
{
	this->dataset = dataset;
};

void DeepLearning::setup(int amountOfHiddenNeuron, int amountOfNeuron, int nbTags, double learningRate)
{
	
	this->learningRate = learningRate;
	this->amountOfHiddenNeuron = amountOfHiddenNeuron;
	this->amountOfNeuron = amountOfNeuron;
	this->nbTags = nbTags;

	this->weightsHidden = { {0.,0.1,0.15,0.05},{0., 0.12,0.18,0.08} };
	this->weightsOutput = { {0.,0.1,0.14},{0.,0.125,0.21},{0.,0.13,0.07} };
}

void DeepLearning::learn(double stopError, int maxEpoc, ActivationFunction* aFunction)
{
	for (int i = 0; i < maxEpoc; i++)
	{
		if (stopError != 0.)
		{
			double E = executeOneEpoc(stopError, aFunction);
			if (E < stopError)
			{
				break;
			}
		}
		else 
		{
			// tant que nb erreur != 0
		}
	}
}

double DeepLearning::executeOneEpoc(double stopThreadshold, ActivationFunction* aFunction)
{
	double E = 0.0;
	for (int k = 0; k < dataset.size(); k++)
	{
		// Etape 1
		// sous vecteur contenant les données sans les étiquettes (+ 1 pour prendre en compte le biais)
		vector<double> example(dataset[k].begin(), dataset[k].begin() + nbTags);
		// Potentiel des neurones cachés

		// TODO fonction récursive

		vector<double> kC = calculatePotentials(example, amountOfHiddenNeuron, weightsHidden);
		// Sortie des neurones cachés
		vector<double> y = calculateOutputs(kC, amountOfHiddenNeuron, aFunction);
		// Potentiel des neurones de sortie
		vector<double> outputs = calculatePotentials(y, amountOfNeuron, weightsOutput);
		// Sortie des neurones de sortie
		vector<double> zOutputs = calculateOutputs(outputs, amountOfNeuron, aFunction);

		E = calculateEMeanQuad(dataset[k], zOutputs, nbTags);
		if (E < stopThreadshold) break;
		// Etape 2a
		// Calcul signal d'erreur couche de sortie
		vector<double> outputSigError = caclulateOutputSigError(dataset[k], zOutputs, nbTags, amountOfNeuron);
		// Etape 2b
		// Calcul signal d'erreur couche caché (biais pris en compte)
		vector<double> hiddenOutputSigError = caclulateHiddenSigError(y, amountOfHiddenNeuron);

		// cumulation des signaux d'erreur des neurones couche cachée de sorties qui leurs sont liés
		vector<double> cumulHiddenLayer = cumulHiddenLayerSigError(hiddenOutputSigError, outputSigError, amountOfNeuron, amountOfHiddenNeuron);

		// Etape 3a
		editWeights(outputSigError, y, weightsOutput);
		// Etape 3b (c+1 pour ne pas prendre en compte du biais)
		editWeights(cumulHiddenLayer, example, weightsHidden);

	}
	return E;
}

vector<double> DeepLearning::calculatePotentials(vector<double> outputs, int amountOfNeuron, vector<vector<double>> weights)
{
 	vector<double> outputsTmp;
	for (int p = 0; p < amountOfNeuron; p++)
	{
		double pCurrent = weights[p][0]; // biais 
		for (int w = 1; w < weights[0].size(); w++)
		{
			pCurrent += weights[p][w] * outputs[w - 1];
		}
		outputsTmp.push_back(pCurrent);
	}
	return outputsTmp;
}

vector<double> DeepLearning::calculateOutputs(vector<double> outputs, int amountOfNeuron, ActivationFunction* aFunction)
{
	vector<double> zOutputs;
	for (int z = 0; z < amountOfNeuron; z++)
	{
		zOutputs.push_back(aFunction->compute(outputs[z]));
	}
	return zOutputs;
}

double DeepLearning::calculateEMeanQuad(vector<double> example, vector<double> outputs, int nbTags)
{
	double E = 0.0;
	// boucle sur les étiquettes de l'example
	for (int i = 0; i < nbTags; i++)
	{
		double tag = example[i + (example.size() - nbTags)];
		E += pow(tag - outputs[i], 2);
	}
	return E * 0.5;
}

vector<double> DeepLearning::caclulateOutputSigError(vector<double> example, vector<double> zOutputs, int nbTags, int amountOfNeuron)
{
	vector<double> outputSigError;
	for (int s = 0; s < amountOfNeuron; s++)
	{
		double tag = example[s + (example.size() - nbTags)];
		double sig = (tag - zOutputs[s]) * zOutputs[s] * (1 - zOutputs[s]);
		outputSigError.push_back(sig);
	}
	return outputSigError;
}

vector<double> DeepLearning::caclulateHiddenSigError(vector<double> hiddenLayerOutputs, int amountOfNeuron)
{
	vector<double> hiddenOutputSigError;
	for (int c = 0; c < amountOfNeuron; c++)
	{
		double sig = hiddenLayerOutputs[c] * (1 - hiddenLayerOutputs[c]);
		hiddenOutputSigError.push_back(sig);
	}
	return hiddenOutputSigError;
}
vector<double> DeepLearning::cumulHiddenLayerSigError(vector<double> hiddenOutputSigError, vector<double> outputSigError, int amountOfNeuron, int amountOfHiddenNeuron)
{
	vector<double> cumulHiddenLayer;
	for (int c = 0; c < amountOfHiddenNeuron; c++)
	{
		double cumul = 0.0;
		for (int s = 0; s < amountOfNeuron; s++)
		{
			cumul += outputSigError[s] * weightsOutput[s][c + 1];
		}
		cumul *= hiddenOutputSigError[c];
		cumulHiddenLayer.push_back(cumul);
	}
	return cumulHiddenLayer;
}

void DeepLearning::editWeights(vector<double> sigError, vector<double> example, vector<vector<double>> weights)
{
	for (int c = 0; c < weights.size(); c++)
	{
		weights[c][0] += learningRate * sigError[c] * 1.;
		for (int e = 1; e < weights[c].size(); e++)
		{
			weights[c][e] += learningRate * sigError[c] * example[e - 1];
		}
	}
}