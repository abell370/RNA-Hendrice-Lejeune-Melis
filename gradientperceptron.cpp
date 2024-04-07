#include "gradientperceptron.h"

#include <math.h>
#include <iostream>
#include <iterator>     // std::ostream_iterator
#include <vector>       // std::vector
#include <algorithm>    // std::copy
#include <iterator>
using namespace std;


GradientPerceptron::GradientPerceptron() : result(0.) {};


void GradientPerceptron::setup(vector<vector<double>> dataset, vector<double> weights, double learningRate)
{
    this->n = learningRate;
    this->data = dataset;
    this->weights = weights;
}

void GradientPerceptron::learn(int maxIter, double minMeanQuadraticError, int indexOfPredictedData, ActivationFunction* activation, int maxClassificationError) {
	this->reset(); // empty iterations
	for (int i = 0; i < maxIter; i++)
	{
		double eMoy = this->executeOneIteration(indexOfPredictedData,activation);
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

double GradientPerceptron::executeOneIteration(int indexOfPredicted, ActivationFunction* activation)
{
	this->iterations += 1;
	Iteration iter = Iteration();
	this->nbErreurs = 0;
	int weightsSize = this->weights.size();
	vector<double> wCorrections(weightsSize);
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
		if (s != this->data[k][indexOfPredicted])
		{
			this->nbErreurs++;
		}

		double e = this->data[k][indexOfPredicted] - y;
		this->weights[0] += wCorrections[0] + this->n * e * 1.;
		for (int i = 1; i < weightsSize; i++)
		{
			wCorrections[i] = wCorrections[i] + this->n * e * this->data[k][i - 1];
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
	return this->calculMeanQuadratic(indexOfPredicted, activation);
}


double GradientPerceptron::calculMeanQuadratic(int indexOfPredictedData, ActivationFunction* activation)
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

string GradientPerceptron::getResult()
{
	return "nbIter= " + to_string(this->iterations) + " eMoy= " + to_string(this->result);
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

