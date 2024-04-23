#include "history.h"
#include "iteration.h"


void History::addEpoc(Iteration* iteration)
{
	this->history.push_back(iteration);
}

void History::addEpocs(vector<Iteration*> epocs)
{
	for (Iteration* iter : epocs)
		this->history.push_back(iter);

}
vector<Iteration*> History::getHistory()
{
	return this->history;
}