#include "adalineperceptron.h"

#include <math.h>
#include <iostream>
#include <iterator>     // std::ostream_iterator
#include <vector>       // std::vector
#include <algorithm>    // std::copy
#include <iterator>
using namespace std;


AdalinePerceptron::AdalinePerceptron() 
{
	this->result = { .0, .0 };
};

void AdalinePerceptron::setup(vector<vector<double>> dataset, vector<double> weights, double learningRate)
{
        this->n = learningRate;
        this->data = dataset;
        this->weights = weights;
}

void AdalinePerceptron::learn(int maxIter, double minMeanQuadraticError, int indexOfPredictedData) {
    this->reset(); // empty iterations
	if (minMeanQuadraticError != NULL)
	{
		this->loopOnIterations(minMeanQuadraticError, maxIter, indexOfPredictedData);
	}
	else
	{
		this->loopWhileErrorNotNull(maxIter, indexOfPredictedData);
	}
}


void AdalinePerceptron::loopOnIterations(float minErrorAccepted, int maxEpoc, int indexOfPredictedData)
{
	for (int i = 1; i <= maxEpoc; i++)
	{
		double eMoy = this->executeOneIteration(indexOfPredictedData);
		this->result[0] = i;
		if (eMoy < minErrorAccepted)
		{
			this->result[1] = eMoy;
			break;
		}
	}
}

void AdalinePerceptron::loopWhileErrorNotNull(int maxEpoc, int indexOfPredictedData)
{
	for (int i = 1; i <= maxEpoc; i++)
	{
		double eMoy = this->executeOneIteration(indexOfPredictedData);
		this->result[0] = i;
		if (this->nbErreurs == 0)
		{
			this->result[1] = eMoy;
			break;
		}
	}
}

double AdalinePerceptron::executeOneIteration(int indexOfPredictedData)
{
	Iteration iter = Iteration();
	this->nbErreurs = 0;
	int weightsSize  = this->weights.size();
	for (uint k = 0; k < this->data.size(); k++)
	{
		double potential = 0.0;
		for (int x = 0; x < weightsSize; x++)
		{
			potential += this->weights[x] * this->data[k][x];
		}
		int s = potential >= 0 ? 1 : -1;
		//  example[weightsSize] = predicted
		if (s != this->data[k][indexOfPredictedData])
		{
			this->nbErreurs += 1;
		}
		double localError = this->data[k][indexOfPredictedData] - potential;

		iter.addStep({
		  k,
		  this->weights,
		  this->data[k], potential, this->data[k][indexOfPredictedData], localError
		});

		for (int x = 0; x < weightsSize; x++)
		{
			this->weights[x] += this->n * localError * this->data[k][x];
		}
	}
	this->addIteration(iter);
	return this->calculMeanQuadratic(indexOfPredictedData);
}

double AdalinePerceptron::calculMeanQuadratic(int indexOfPredictedData)
{
	double E = 0.0;
	for (vector<double> example : data) {
		double y = 0.0;
		for (int x = 0; x < this->weights.size(); x++) {
			y += this->weights[x] * example[x];
		}
		E += pow(example[indexOfPredictedData] - y, 2);
	}
	double eMoy = (0.5 * E) / data.size();
	return eMoy;
}

string AdalinePerceptron::getResult()
{
	return "nbIter= "+to_string(this->result[0])+" eMoy= "+ to_string(this->result[1]);
}
/*
QVector<double> AdalinePerceptron::calcGraph(uint iterationIndex, std::vector<double> x1) {
    
        To calc line equation

        w0*x0 + w1*x1 + x2*w2 = 0

        so, for each given x1 we need to find x2

        x2 = (-w0*x0 - w1*x1)/w2
    
    QVector<double> x2 = QVector<double>(x1.size());

    if (iterationIndex < this->getIterations().size()) {
        Iteration iteration = this->getIterations()[iterationIndex];
        Step lastStep = iteration.getSteps()[iteration.getSteps().size() - 1];

        for (unsigned i = 0; i < x1.size(); i++) {
            x2[i] = (-lastStep.weights[0] * 1 - lastStep.weights[1] * x1[i]) / lastStep.weights[2];
        }
    }

    return x2;
}
*/

