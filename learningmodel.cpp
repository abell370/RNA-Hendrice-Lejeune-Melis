#include "learningmodel.h"

/*
	Classe de base permettant d'exécuter soit un modèle mono-couche soit multi-couche.
*/
LearningModel::LearningModel(vector<vector<double>> dataset, ActivationFunction* activation, vector<double> weights, double learningRate)
{
    this->dataset = dataset;
    this->activation = activation;
    this->n = learningRate;
    this->weights = weights;
}

void LearningModel::learn(int maxIter, double minMeanQuadraticError, int indexOfPredictedData, int maxClassificationError) {
	if (minMeanQuadraticError != 0.) maxClassificationError = -1;
	this->reset(); // empty iterations
	int i = 0;
	bool thresholdReached = false;
	do {
		double eMoy = this->executeOneIteration(indexOfPredictedData, true);
		addIteration(new Iteration(Iteration(this->nbErreurs, eMoy, { this->weights })));
		if (eMoy < minMeanQuadraticError) thresholdReached = true;
		i += 1;
	} while (!thresholdReached && i < maxIter && this->nbErreurs > maxClassificationError);
}

std::vector<Iteration*> LearningModel::getIterations() {
    return this->iterationsSaved;
}

std::string LearningModel::getName() {
    return "LearningModel";
}

vector<double> LearningModel::getWeights() {
    return this->weights;
}

void LearningModel::addIteration(Iteration* iteration) {
    iterationsSaved.push_back(iteration);
}

void LearningModel::reset() {
    iterationsSaved.clear();
}

