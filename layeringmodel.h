#pragma once
#include "activationfunction.h"
#include <vector>
#include <map>
#include <string>
#include "history.h"

using namespace std;

/*
	Classe de base utilisée pour exécuter les différentes 'architecture' d'apprentissage (mono-couche, multi-couche)
*/
class LayeringModel
{
public:

	LayeringModel(vector<vector<double>> dataset, vector<ActivationFunction*> activation);

	virtual History* train(double stopThreadshold, int maxEpoc, int maxClassificationError) = 0;
	virtual map<string, double> checkAccuracy(vector<vector<double>> validationDataset) = 0;
	virtual void reset() = 0;
	virtual vector<double> predict(vector<double> input) = 0;

protected:
	vector<vector<double>> dataset;
	vector<double> eMoyDuringTraining;
	vector<ActivationFunction*> aFunction;

	vector<double> generateRandom(int size);
};

