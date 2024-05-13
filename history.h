#pragma once

#include "iteration.h"
#include <vector>

/*
	Classe stockant toutes les donn�es r�cup�r�es pendant un apprentissage. Les donn�es sauvegard�es sont utilis�es pour afficher 
	les diff�rents graphes.
*/
class History
{
public:
	History() {};
	~History() {};

	void addEpoc(Iteration* iteration);
	void addEpocs(vector<Iteration*> epocs);
	std::vector<Iteration*> getHistory();
	int size();
	double getMSE(int epoc);
	vector<double> getMSEEvolution();
	int getClassification(int epoc);
	string getLabel(int epoc);
	vector<vector<double>> getWeights(int epoc);
	unsigned int getIterationCount();
private:
	std::vector<Iteration*> history;

	unsigned int getAbsoluteIterNb(int startindex, int epoc);
	vector<int> getNeuronsStart();
};

