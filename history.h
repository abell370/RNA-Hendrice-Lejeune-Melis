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

private:
	std::vector<Iteration*> history;
};

