#pragma once
#include <vector>
using namespace std;

class DeepLearning
{
public:
	DeepLearning(vector<vector<double>> dataset, vector<double> etiquets, vector<vector<double>> weigthsHidden, vector<vector<double>> weigthsOutput, double learningRate);
	~DeepLearning() {};

	void learn(int hiddenLayerSize, int outputLayerSize, double stopThreadshold);

private:
	vector<vector<double>> dataset, weigthsHidden, weigthsOutput;
	vector<double> tags;
	double learningRate;
};

