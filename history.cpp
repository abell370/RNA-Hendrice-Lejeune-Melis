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

vector<double> History::getMSEEvolution() {
	unsigned int iterationMax = getIterationCount();
	vector<double> evolution;

	vector<int> neuronStartIndices = getNeuronsStart();

	for (int i = 0; i < iterationMax; ++i) {
		double errorSum = 0;

		for (int neuronStart : neuronStartIndices) {
			int target = getAbsoluteIterNb(neuronStart, i);
			errorSum += getMSE(target);
		}

		evolution.push_back(errorSum);
	}
	return evolution;
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
	vector<int> neuronStartIndices = getNeuronsStart();

	if (neuronStartIndices.size() > 1) {
		vector<vector<double>> weights;

		for (int i = 0; i < neuronStartIndices.size(); ++i) {
			int startIndex = neuronStartIndices[i];
			int target = getAbsoluteIterNb(startIndex, epoc);
			weights.push_back(history[target]->getWeights()[0]);
		}
		return weights;
	}
	else {
		return this->history[epoc]->getWeights();
	}
}

unsigned int History::getIterationCount() {
	vector<int> iterPerNeuron;
	int iterNb = 0;
	string label = "";
	for (int i = 0, pos = -1; i < history.size(); ++i) {
		if (label != getLabel(i)) {
			label = getLabel(i);
			iterPerNeuron.push_back(1);
			pos++;
		}
		else {
			iterPerNeuron[pos]++;
		}
	}

	if (iterPerNeuron.size() > 1) {
		int max = 0;
		for (int iter : iterPerNeuron) {
			if (iter > max) {
				max = iter;
			}
		}
		return max;
	}
	else {
		return history.size();
	}
}

unsigned int History::getAbsoluteIterNb(int startIndex, int epoc) {
	vector<int> neuronStartIndices = getNeuronsStart();
	
	if (neuronStartIndices.size() > 1) {
		for (int i = 0; i < neuronStartIndices.size(); ++i) {
			if (startIndex == neuronStartIndices[i]) {
				int target;
				if (i == neuronStartIndices.size() - 1) {// Si dernier neurone
					if (startIndex + epoc < history.size()) {// Vérifie si va pas out of bounds
						target = startIndex + epoc;
					}
					else {
						target = history.size() - 1;
					}
				}
				else {
					int nextIndex = neuronStartIndices[i + 1];
					if (startIndex + epoc < nextIndex) {
						target = startIndex + epoc;
					}
					else {// Si atteint début d'autre neurone, s'arrete avant
						target = nextIndex - 1;
					}
				}
				return target;
			}
		}
	}
	else {
		return startIndex + epoc;
	}
}

vector<int> History::getNeuronsStart(){
	vector<int> neuronStartIndices = {};
	string label = "";
	for (int i = 0; i < history.size(); ++i) {
		if (label != getLabel(i)) {
			label = getLabel(i);
			neuronStartIndices.push_back(i);
		}
	}
	return neuronStartIndices;
}
