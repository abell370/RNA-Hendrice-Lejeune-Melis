#include "deeplearning.h"

DeepLearning::DeepLearning(vector<vector<double>> dataset, vector<double> tags, vector<vector<double>> weigthsHidden, vector<vector<double>> weigthsOutput, double learningRate) 
{
	this->dataset = dataset;
	this->tags = tags;
	this->weigthsHidden = weigthsHidden;
	this->weigthsOutput = weigthsOutput;
	this->learningRate = learningRate;
};

void DeepLearning::learn(int hLayerSize, int oLayerSize, double stopError)
{
	for (int k = 0; k < dataset.size(); k++)
	{
		vector<double> kC;
		// Etape 1
		vector<double> example = dataset[k];
		// Potentiel des neurones cachés
		for (int c = 0; c < hLayerSize; c++)
		{
			double kCurrent = 0.0;
			for (int w = 0; w < weigthsHidden[0].size(); w++)
			{
				kCurrent += weigthsHidden[c][w] * example[w];
			}
			kC.push_back(kCurrent);
		}
		// Sortie des neurones cachés
		vector<double> y;
		y.push_back(1);
		for (int c = 0; c < hLayerSize; c++)
		{
			double yC = 1 / (1 + exp(-kC[c]));
			y.push_back(yC);
		}
		// Potentiel des neurones de sortie
		vector<double> outputs;
		for (int p = 0; p < oLayerSize; p++)
		{
			double pCurrent = 0.0;
			for (int w = 0; w < weigthsOutput[0].size(); w++)
			{
				pCurrent += weigthsOutput[p][w] * y[w];
			}
			outputs.push_back(pCurrent);
		}
		// Sortie des neurones de sortie
		vector<double> zOutputs;
		for (int z = 0; z < oLayerSize; z++)
		{
			double zCurrent = 1 / (1 + exp(-outputs[z]));
			zOutputs.push_back(zCurrent);
		}
		int startEtiquetIndex = example.size() - 3;

		double E = 0.0;
		// boucle sur les étiquettes de l'example
		for (int i = 0; i < zOutputs.size(); i++)
		{
			E += pow(tags[i] - zOutputs[i], 2);
		}
		E *= 0.5;
		if (E < stopError) break;
		// Etape 2a
		// Calcul signal d'erreur couche de sortie
		vector<double> outputSigError;
		for (int s = 0; s < oLayerSize; s++)
		{
			double sig = (tags[s] - zOutputs[s]) * zOutputs[s] * (1 - zOutputs[s]);
			outputSigError.push_back(sig);
		}

		// Etape 2b
		// Calcul signal d'erreur couche caché (biais pris en compte)
		vector<double> hiddenOutputSigError;
		for (int c = 0; c < oLayerSize; c++)
		{
			double sig = y[c] * (1 - y[c]);
			hiddenOutputSigError.push_back(sig);
		}

		// cumulation des signaux d'erreur des neurones couche cachée de sorties qui leurs sont liés
		vector<double> cumulHiddenLayer;
		for (int c = 0; c < 3; c++)
		{
			double cumul = 0.0;
			for (int s = 0; s < oLayerSize; s++)
			{
				cumul += outputSigError[s] * weigthsOutput[s][c];
			}
			cumul *= hiddenOutputSigError[c];
			cumulHiddenLayer.push_back(cumul);
		}

		// Etape 3a
		for (int s = 0; s < weigthsOutput.size(); s++)
		{
			for (int c = 0; c < weigthsOutput[s].size(); c++)
			{
				weigthsOutput[s][c] += learningRate * outputSigError[s] * y[c];
			}
		}

		// Etape 3b (c+1 pour ne pas prendre en compte du biais)
		for (int c = 0; c < hLayerSize; c++)
		{
			for (int e = 0; e < weigthsHidden[c].size(); e++)
			{
				weigthsHidden[c][e] += learningRate * cumulHiddenLayer[c + 1] * example[e];
			}
		}
		// on continue l'apprentissage
		learn(hLayerSize, oLayerSize, stopError);
	}
}