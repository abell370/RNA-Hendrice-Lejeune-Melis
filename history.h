#pragma once

#include "iteration.h"
#include <vector>

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
	int getClassification(int epoc);
	string getLabel(int epoc);

private:
	std::vector<Iteration*> history;
};

