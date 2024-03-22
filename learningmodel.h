#ifndef LEARNINGMODEL_H
#define LEARNINGMODEL_H

#include <vector>
#include "iteration.h"

using namespace std;

class LearningModel
{
    vector<Iteration> iterations;
public:
    virtual void setup(vector<vector<double>> dataset, vector<double> weights, double learningRate);
    virtual void learn(int maxIter, double minMeanQuadraticError, int indexOfPredictedData);
    virtual QVector<double> calcGraph(uint iterationIndex, std::vector<double> x1);
    virtual std::string getName() = 0;

    vector<Iteration> getIterations();
    void reset();
protected:
    void addIteration(Iteration iteration);
};



#endif // LEARNINGMODEL_H
