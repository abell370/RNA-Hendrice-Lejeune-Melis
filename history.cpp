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

int History::size()
{
	return this->history.size();
}

double History::getMSE(int epoc)
{
	return this->history[epoc]->getMSE();
}

int History::getClassification(int epoc)
{
	return this->history[epoc]->getClassificationE();

}

string History::getLabel(int epoc)
{
	return this->history[epoc]->getLabel();

}

vector<vector<double>> History::getWeights(int epoc) {
	return this->history[epoc]->getWeights();
}