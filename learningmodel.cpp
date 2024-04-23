#include "learningmodel.h"

LearningModel::LearningModel(vector<vector<double>> dataset, ActivationFunction* activation, vector<double> weights, double learningRate)
{
    this->dataset = dataset;
    this->activation = activation;
    this->n = learningRate;
    this->weights = weights;
    this->result = 0.;
}

void LearningModel::learn(int maxIter, double minMeanQuadraticError, int indexOfPredictedData, int maxClassificationError) {
	this->reset(); // empty iterations
	for (int i = 0; i < maxIter; i++)
	{
		double eMoy = this->executeOneIteration(indexOfPredictedData, true);
		this->result = eMoy;
		Iteration* iter = new Iteration(Iteration(this->nbErreurs, eMoy));
		addIteration(iter);
		if (minMeanQuadraticError != 0. && eMoy < minMeanQuadraticError)
		{
			break;
		}
		else
		{
			if (this->nbErreurs <= maxClassificationError)
			{
				break;
			}
		}
	}

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

