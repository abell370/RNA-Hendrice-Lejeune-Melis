#include "iteration.h"

map<string, double> Iteration::getData()
{
	return { {this->label + "_mse", this->eMoy},{this->label + "_classification_error", (double)this->classificationError} };
}

void Iteration::setLabel(string label)
{
	this->label = label;
}