#ifndef LEARNINGMODEL_H
#define LEARNINGMODEL_H

#include <vector>
#include "iteration.h"

using namespace std;

class LearningModel
{
    vector<Iteration> iterations;
public:
    virtual void setup(vector<vector<double>> dataset, vector<double> weights, double learningRate) = 0;
    virtual void learn(int maxIter, double minMeanQuadraticError, int indexOfPredictedData) = 0;
    virtual std::string getName() = 0;

    vector<Iteration> getIterations();
    void reset();

protected:
    void addIteration(Iteration iteration);
};



#endif // LEARNINGMODEL_H
