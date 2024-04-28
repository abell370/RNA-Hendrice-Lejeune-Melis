#include "gradientperceptron.h"

#include <math.h>
#include <iostream>
#include <iterator>     // std::ostream_iterator
#include <vector>       // std::vector
#include <algorithm>    // std::copy
#include <iterator>
#include <map>

using namespace std;

map<string, double> GradientPerceptron::checkAccuracy(int tagIndex)
{
	this->nbErreurs = 0;
	this->iterations = 0;
	double E = this->executeOneIteration(tagIndex, false);
	return {
		{"nbErreurs", this->nbErreurs},
		{"eMoy", E},
		{"nbIteration", this->iterations}
	};
}

double GradientPerceptron::executeOneIteration(int indexOfPredicted, bool updateWeights)
{
	this->iterations += 1;
	this->nbErreurs = 0;
	int weightsSize = this->weights.size();
	vector<double> wCorrections(weightsSize);
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
		if (s != this->dataset[k][indexOfPredicted])
		{
			this->nbErreurs++;
		}

		double e = this->dataset[k][indexOfPredicted] - y;
		wCorrections[0] += this->n * e * 1.;
		for (int i = 1; i < weightsSize; i++)
		{
			wCorrections[i] += this->n * e * this->dataset[k][i - 1];
		}
	}
	if (updateWeights)
	{
		// correction wi
		for (int w = 0; w < weightsSize; w++)
		{
			this->weights[w] += wCorrections[w];
		}
	}
	double mse = this->calculMeanQuadratic(indexOfPredicted);
	// eMoy quad
	return mse;
}


double GradientPerceptron::calculMeanQuadratic(int indexOfPredictedData)
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
