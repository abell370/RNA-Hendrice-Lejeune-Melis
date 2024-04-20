#include "deeplearning.h"
#include "utils.h"

void MultiLayer::setup(int amountOfHiddenNeuron, int nbClasses, double learningRate)
{
	this->learningRate = learningRate;
	this->amountOfHiddenNeuron = amountOfHiddenNeuron;
	// Cas d'un apprentissage avec 2 classes => 1 neurone de sorite suffit SINON besoin de n neurones de sorties pour n classes
	nbClasses == 2 ? this->nbTags = 1 : this->nbTags = nbClasses;
	int amountOfEntry = this->dataset[0].size() - this->nbTags;
	// + 1 pour le biais
	for (int w = 0; w < amountOfHiddenNeuron; w++)
	{
		this->weightsHidden.push_back(Utils::generateRandom(amountOfEntry + 1));
	}
	for (int y = 0; y < this->nbTags; y++)
	{
		this->weightsOutput.push_back(Utils::generateRandom(amountOfHiddenNeuron + 1));
	}
}

map<string, double> MultiLayer::checkAccuracy(vector<vector<double>> validationDataset)
{
	this->dataset = validationDataset;
	this->classificationErrors = 0;
	double E = executeOneEpoc(0., false); // on exécute une époc et on regarde ne nombre d'erreur de classification avec les poids actuels
	return {
		{"eMoy", E},
		{"Amount of classification error", this->classificationErrors}
	};
};

void MultiLayer::train(double stopError, int maxEpoc, int maxClassificationError)
{
	for (int i = 0; i < maxEpoc; i++)
	{
		this->nbEpoc += 1;
		double E = executeOneEpoc(stopError, true);
		if (stopError != 0.)
		{
			if (E < stopError) break;
		}
		else 
		{
			if (this->classificationErrors <= maxClassificationError) break;
		}
	}
}

// Adaline is used 
double MultiLayer::executeOneEpoc(double stopThreadshold, bool updateWeights)
{
	double E = 0.0;
	this->classificationErrors = 0;
	for (int k = 0; k < dataset.size(); k++)
	{
		// Etape 1
		// sous vecteur contenant les données sans les étiquettes (+ 1 pour prendre en compte le biais)
		vector<double> example(dataset[k].begin(), dataset[k].end() - nbTags);
		// Potentiel des neurones cachés

		// TODO fonction récursive

		vector<double> kC = calculatePotentials(example, amountOfHiddenNeuron, weightsHidden);
		// Sortie des neurones cachés
		vector<double> y = calculateOutputs(kC, amountOfHiddenNeuron);
		// Potentiel des neurones de sortie
		vector<double> outputs = calculatePotentials(y, nbTags, weightsOutput);
		// Sortie des neurones de sortie
		vector<double> zOutputs = calculateOutputs(outputs, nbTags);

		// classification
		for (int t = 0; t < nbTags; t++)
		{
			double tag = example[t + (example.size() - nbTags)];
			for (double z : zOutputs)
			{
				double thresholded = this->aFunction->performThresholding(z);
				if (thresholded != tag) this->classificationErrors += 1;
			}
		}

		E = calculateEMeanQuad(dataset[k], zOutputs, nbTags);
		if (E < stopThreadshold) break;

		if (updateWeights)
		{
			// Etape 2a
			// Calcul signal d'erreur couche de sortie
			vector<double> outputSigError = caclulateOutputSigError(dataset[k], zOutputs, nbTags, nbTags);
			// Etape 2b
			// Calcul signal d'erreur couche caché (biais pris en compte)
			vector<double> hiddenOutputSigError = caclulateHiddenSigError(y, amountOfHiddenNeuron);

			// cumulation des signaux d'erreur des neurones couche cachée de sorties qui leurs sont liés
			vector<double> cumulHiddenLayer = cumulHiddenLayerSigError(hiddenOutputSigError, outputSigError, nbTags, amountOfHiddenNeuron);

			// Etape 3a
			editWeights(outputSigError, y, weightsOutput);
			// Etape 3b (c+1 pour ne pas prendre en compte du biais)
			editWeights(cumulHiddenLayer, example, weightsHidden);
		}
	}
	return E;
}

vector<double> MultiLayer::calculatePotentials(vector<double> outputs, int amountOfNeuron, vector<vector<double>> weights)
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

vector<double> MultiLayer::calculateOutputs(vector<double> outputs, int amountOfNeuron)
{
	vector<double> zOutputs;
	for (int z = 0; z < amountOfNeuron; z++)
	{
		zOutputs.push_back(this->aFunction->compute(outputs[z]));
	}
	return zOutputs;
}

double MultiLayer::calculateEMeanQuad(vector<double> example, vector<double> outputs, int nbTags)
{
	double E = 0.0;
	// boucle sur les étiquettes de l'example
	for (int i = 0; i < nbTags; i++)
	{
		double tag = example[i + (example.size() - nbTags)];
		E += pow(tag - outputs[i], 2);
	}
	return (.5 * E) / this->dataset.size();
}

vector<double> MultiLayer::caclulateOutputSigError(vector<double> example, vector<double> zOutputs, int nbTags, int amountOfNeuron)
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

vector<double> MultiLayer::caclulateHiddenSigError(vector<double> hiddenLayerOutputs, int amountOfNeuron)
{
	vector<double> hiddenOutputSigError;
	for (int c = 0; c < amountOfNeuron; c++)
	{
		double sig = hiddenLayerOutputs[c] * (1 - hiddenLayerOutputs[c]);
		hiddenOutputSigError.push_back(sig);
	}
	return hiddenOutputSigError;
}
vector<double> MultiLayer::cumulHiddenLayerSigError(vector<double> hiddenOutputSigError, vector<double> outputSigError, int amountOfNeuron, int amountOfHiddenNeuron)
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

void MultiLayer::editWeights(vector<double> sigError, vector<double> example, vector<vector<double>> weights)
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


vector<vector<double>> MultiLayer::getDecisionWeights() {
	return this->weightsOutput;
}

// TODO
void MultiLayer::getResult() 
{
	string result = "nb epoc / nbError [" + to_string(this->nbEpoc) + " / " + to_string(this->classificationErrors) + "]";
};
void MultiLayer::reset() {};