﻿#include "gradientperceptron.h"

#include <math.h>
#include <iostream>
#include <iterator>     // std::ostream_iterator
#include <vector>       // std::vector
#include <algorithm>    // std::copy
#include <iterator>
using namespace std;


GradientPerceptron::GradientPerceptron() : result({ .0, .0 }) {};


void GradientPerceptron::setup(vector<vector<double>> dataset, vector<double> weights, double learningRate)
{
    this->n = learningRate;
    this->data = dataset;
    this->weights = weights;
}

void GradientPerceptron::learn(int maxIter, double minMeanQuadraticError, int indexOfPredictedData, ActivationFunction* activation) {
	this->reset(); // empty iterations
	for (int i = 0; i < maxIter; i++)
	{
		double eMoy = this->executeOneIteration(indexOfPredictedData,activation);
		this->result[0] = i;
		this->result[1] = eMoy;

		if (minMeanQuadraticError != NULL)
		{

			if (eMoy < minMeanQuadraticError)
			{
				break;
			}
		}
		else
		{
			if (this->nbErreurs == 0)
			{
				break;
			}
		}
	}

}

double GradientPerceptron::executeOneIteration(int indexOfPredicted, ActivationFunction* activation)
{
	Iteration iter = Iteration();
	this->nbErreurs = 0;
	int weightsSize = this->weights.size();
	vector<double> wCorrections(weightsSize);
	for (uint k = 0; k < this->data.size(); k++)
	{
		double p = 0.0;
		for (int x = 0; x < weightsSize; x++)
		{
			p += this->weights[x] * this->data[k][x];
		}
		double y = activation->compute(p);
		// classification
		int s = y >= 0 ? 1 : -1;
		if (s != this->data[k][indexOfPredicted])
		{
			this->nbErreurs++;
		}

		double e = this->data[k][indexOfPredicted] - y;
		for (int i = 0; i < weightsSize; i++)
		{
			wCorrections[i] = wCorrections[i] + this->n * e * this->data[k][i];
		}
		iter.addStep({
		  k,
		  this->weights,
		  this->data[k], y, this->data[k][indexOfPredicted], e
		});
	}

	// correction wi
	for (int w = 0; w < weightsSize; w++)
	{
		this->weights[w] = this->weights[w] + wCorrections[w];
	}
	this->addIteration(iter);
	// eMoy quad
	return this->calculMeanQuadratic(indexOfPredicted);
}


double GradientPerceptron::calculMeanQuadratic(int indexOfPredictedData)
{
	double E = 0.0;
	for (vector<double> example : data) {
		double y = 0.0;
		for (int x = 0; x < this->weights.size(); x++) {
			y += weights[x] * example[x];
		}
		E += pow(example[indexOfPredictedData] - y, 2);
	}
	double eMoy = (0.5 * E) / data.size();
	return eMoy;
}

string GradientPerceptron::getResult()
{
	return "nbIter= " + to_string(this->result[0]) + " eMoy= " + to_string(this->result[1]);
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

