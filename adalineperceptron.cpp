#include "adalineperceptron.h"

#include <math.h>
#include <iostream>
#include <iterator>     // std::ostream_iterator
#include <vector>       // std::vector
#include <algorithm>    // std::copy
#include <iterator>
#include <map>

using namespace std;

map<string, double> AdalinePerceptron::checkAccuracy(int tagIndex)
{
	this->nbErreurs = 0;
	this->iterations = 0;
	double E = executeOneIteration(tagIndex, false);
	return {
		{"nbErreurs", this->nbErreurs},
		{"eMoy", E},
		{"nbIteration", this->iterations}
	};
}

double AdalinePerceptron::executeOneIteration(int indexOfPredictedData, bool updateWeights)
{
	this->iterations += 1;
	this->nbErreurs = 0;
	int weightsSize = this->weights.size();
	for (int k = 0; k < this->dataset.size(); k++)
	{
		double p = this->weights[0];
		for (int x = 1; x < weightsSize; x++)
		{
			p += this->weights[x] * this->dataset[k][x - 1];
		}
		double y = activation->compute(p);
		// classification
		double s = activation->performThresholding(y);
		if (s != this->dataset[k][indexOfPredictedData])
		{
			this->nbErreurs++;
		}

		double e = this->dataset[k][indexOfPredictedData] - y;
		if (updateWeights)
		{
			weights[0] += n * e;
			for (int c = 0; c < weights.size() - 1; c++)
			{
				weights[c + 1] += n * e * this->dataset[k][c];
			}
		}
	}
	double mse = this->calculMeanQuadratic(indexOfPredictedData);
	// eMoy quad
	return mse;
}

double AdalinePerceptron::calculMeanQuadratic(int indexOfPredictedData)
{
	double E = 0.;

	vector<double> outputs;
	for (int x = 0; x < dataset.size(); x++)
	{
		double p = this->weights[0];
		for (int w = 1; w < this->weights.size(); w++)
		{
			p += this->weights[w] * this->dataset[x][w - 1];
		}
		double y = activation->compute(p);
		outputs.push_back(y);
	}

	for (int k = 0; k < dataset.size(); k++)
	{
		double error = dataset[k][indexOfPredictedData] - outputs[k];
		E += pow(error, 2);
	}
	
	return (.5 * E) / dataset.size();
}
