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
	this->result = 0.;
};

void AdalinePerceptron::setup(vector<vector<double>> dataset, vector<double> weights, double learningRate)
{
        this->n = learningRate;
        this->data = dataset;
        this->weights = weights;
}

void AdalinePerceptron::learn(int maxIter, double minMeanQuadraticError, int indexOfPredictedData, ActivationFunction* activation, int maxClassificationError) {
    this->reset(); // empty iterations
	for (int i = 0; i < maxIter; i++)
	{
		double eMoy = this->executeOneIteration(indexOfPredictedData, activation);
		this->result = eMoy;

		if (minMeanQuadraticError != 0.)
		{

			if (eMoy < minMeanQuadraticError)
			{
				break;
			}
		}
		else
		{
			if (this->nbErreurs == maxClassificationError)
			{
				break;
			}
		}
	}

}

double AdalinePerceptron::executeOneIteration(int indexOfPredictedData, ActivationFunction* activation)
{
	Iteration iter = Iteration();
	this->iterations += 1;
	this->nbErreurs = 0;
	int weightsSize = this->weights.size();
	for (uint k = 0; k < this->data.size(); k++)
	{
		double p = this->weights[0];
		for (int x = 1; x < weightsSize; x++)
		{
			p += this->weights[x] * this->data[k][x - 1];
		}
		double y = activation->compute(p);
		// classification
		double s = activation->performThresholding(y);
		if (s != this->data[k][indexOfPredictedData])
		{
			this->nbErreurs++;
		}

		double e = this->data[k][indexOfPredictedData] - y;
		iter.addStep({
		  k,
		  this->weights,
		  this->data[k], y, this->data[k][indexOfPredictedData], 
		  e
		});

		weights[0] += n * e;
		for (int c = 0; c < weights.size() - 1; c++)
		{
			weights[c + 1] += n * e * this->data[k][c];
		}
	}

	this->addIteration(iter);
	// eMoy quad
	return this->calculMeanQuadratic(indexOfPredictedData, activation);
}

double AdalinePerceptron::calculMeanQuadratic(int indexOfPredictedData, ActivationFunction* activation)
{
	double E = 0.;

	vector<double> outputs;
	for (int x = 0; x < data.size(); x++)
	{
		double p = this->weights[0];
		for (int w = 1; w < this->weights.size(); w++)
		{
			p += this->weights[w] * this->data[x][w - 1];
		}
		double y = activation->compute(p);
		outputs.push_back(y);
	}

	for (int k = 0; k < data.size(); k++)
	{
		double error = data[k][indexOfPredictedData] - outputs[k];
		E += pow(error, 2);
	}
	
	return (.5 * E) / data.size();
}

string AdalinePerceptron::getResult()
{
	return "nbIter= "+to_string(this->iterations)+" eMoy= "+ to_string(this->result);
}


