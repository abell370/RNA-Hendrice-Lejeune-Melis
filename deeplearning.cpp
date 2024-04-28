#include "deeplearning.h"
#include <iostream>
#include <random>
#include "iteration.h"

void MultiLayer::setup(int amountOfHiddenNeuron, int nbClasses, double learningRate)
{
	this->learningRate = learningRate;
	this->amountOfHiddenNeuron = amountOfHiddenNeuron;
	// Cas d'un apprentissage avec 2 classes => 1 neurone de sorite suffit SINON besoin de n neurones de sorties pour n classes
	nbClasses == 2 ? this->nbTags = 1 : this->nbTags = nbClasses;
	int amountOfEntry = this->dataset[0].size() - this->nbTags;
	this->eMoyDuringTraining.clear();
	// + 1 pour le biais
	for (int w = 0; w < amountOfHiddenNeuron; w++)
	{
		this->weightsHidden.push_back(this->generateRandom(amountOfEntry + 1));
	}
	for (int y = 0; y < this->nbTags; y++)
	{
		this->weightsOutput.push_back(this->generateRandom(amountOfHiddenNeuron + 1));
	}
}

map<string, double> MultiLayer::checkAccuracy(vector<vector<double>> validationDataset)
{
	this->dataset = validationDataset;
	double E = executeOneEpoc(0., false); // on exécute une époc et on regarde ne nombre d'erreur de classification avec les poids actuels
	return {
		{"eMoy", E},
		{"Amount of classification error", this->classificationErrors}
	};
};

History* MultiLayer::train(double stopError, int maxEpoc, int maxClassificationError)
{
	History* history = new History();
	int i = 0;
	bool thresholdReached = false;
	do {
		double mse = executeOneEpoc(stopError, true);
		Iteration* iter = new Iteration(this->classificationErrors, mse);
		iter->setLabel("deepL");
		history->addEpoc(iter);
		if (mse < stopError) thresholdReached = true;
		i += 1;
	} while (!thresholdReached && i < maxEpoc && this->classificationErrors > maxClassificationError);
	return history;
}

// Adaline is used 
double MultiLayer::executeOneEpoc(double stopThreadshold, bool updateWeights)
{
	this->classificationErrors = 0;
	vector<vector<double>> outputsTotal;
	// Pour implémentation de la stratégie Stochiastique pg.86 du cours
	shuffleDataset();
	for (int k = 0; k < dataset.size(); k++)
	{
		// Etape 1
		// sous vecteur contenant les données sans les étiquettes (+ 1 pour prendre en compte le biais)
		vector<double> example(dataset[k].begin(), dataset[k].end() - nbTags);
		// Potentiel des neurones cachés
		vector<double> kC = calculatePotentials(example, amountOfHiddenNeuron, &this->weightsHidden);
		// Sortie des neurones cachés
		vector<double> y = calculateOutputs(kC, amountOfHiddenNeuron);
		// Potentiel des neurones de sortie
		vector<double> outputs = calculatePotentials(y, nbTags, &this->weightsOutput);
		// Sortie des neurones de sortie
		vector<double> zOutputs = calculateOutputs(outputs, nbTags);
		outputsTotal.push_back(zOutputs);
		vector<double> tags(dataset[k].end() - nbTags, dataset[k].end());

		for (int x = 0; x < nbTags; x++)
		{
			double thresholdedPredicted = this->aFunction->performThresholding(zOutputs[x]);
			if (tags[x] != thresholdedPredicted) this->classificationErrors += 1;
		}

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
			editWeights(outputSigError, y, &this->weightsOutput);
			// Etape 3b (c+1 pour ne pas prendre en compte du biais)
			editWeights(cumulHiddenLayer, example, &this->weightsHidden);
		}
	}
	return calculateEQuad(outputsTotal);
}

vector<double> MultiLayer::calculatePotentials(vector<double> outputs, int amountOfNeuron, vector<vector<double>> *weights)
{
 	vector<double> outputsTmp;
	for (int p = 0; p < amountOfNeuron; p++)
	{
		double pCurrent = (*weights)[p][0]; // biais 
		for (int w = 1; w < (*weights)[0].size(); w++)
		{
			pCurrent += (*weights)[p][w] * outputs[w - 1];
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

double MultiLayer::calculateEQuad(const vector<vector<double>>& outputs)
{
	double totalError = 0.;
	int totalExamples = dataset.size();
	int nbTags = outputs[0].size();

	for (int i = 0; i < totalExamples; i++)
	{
		const vector<double>& example = dataset[i];
		const vector<double>& predictedOutputs = outputs[i];

		for (int j = 0; j < nbTags; j++)
		{
			double tag = example[example.size() - nbTags + j]; 
			totalError += pow(tag - predictedOutputs[j], 2);
		}
	}
	// Calculate the mean squared error
	double mse = totalError / (2 * totalExamples); 
	return mse;
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

void MultiLayer::editWeights(vector<double> sigError, vector<double> example, vector<vector<double>> *weights)
{
	for (int c = 0; c < (*weights).size(); c++)
	{
		(*weights)[c][0] += learningRate * sigError[c] * 1.;
		for (int e = 1; e < (*weights)[c].size(); e++)
		{
			(*weights)[c][e] += learningRate * sigError[c] * example[e - 1];
		}
	}
}

vector<vector<double>> MultiLayer::getDecisionWeights() {
	return this->weightsOutput;
}

void MultiLayer::shuffleDataset()
{
	// Randomly shuffle the dataset
	shuffle(dataset.begin(), dataset.end(),default_random_engine());
}
void MultiLayer::reset() {};