#include "layeringmodel.h"

LayeringModel::LayeringModel(vector<vector<double>> dataset, ActivationFunction* activation)
{
	this->dataset = dataset;
	this->aFunction = activation;
}
