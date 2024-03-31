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

void AdalinePerceptron::learn(int maxIter, double minMeanQuadraticError, int indexOfPredictedData, ActivationFunction* activation) {
    this->reset(); // empty iterations
	for (int i = 0; i < maxIter; i++)
	{
		double eMoy = this->executeOneIteration(indexOfPredictedData, activation);
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

double AdalinePerceptron::executeOneIteration(int indexOfPredictedData, ActivationFunction* activation)
{
	Iteration iter = Iteration();
	this->nbErreurs = 0;
	int weightsSize  = this->weights.size();
	for (uint k = 0; k < this->data.size(); k++)
	{
		double p = 0.0;
		for (int x = 0; x < weightsSize; x++)
		{
			p += this->weights[x] * this->data[k][x];
		}
		double y = activation->compute(p);
		int s = y >= 0 ? 1 : -1;
		//  example[weightsSize] = predicted
		if (s != this->data[k][indexOfPredictedData])
		{
			this->nbErreurs += 1;
		}
		double localError = this->data[k][indexOfPredictedData] - y;

		iter.addStep({
		  k,
		  this->weights,
		  this->data[k], y, this->data[k][indexOfPredictedData], localError
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

