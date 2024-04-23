#ifndef LEARNINGMODEL_H
#define LEARNINGMODEL_H

#include <vector>
#include "iteration.h"
#include "activationfunction.h"
#include <string>
#include <map>

using namespace std;

class LearningModel
{
public:

    LearningModel(vector<vector<double>> dataset, ActivationFunction* activation, vector<double> weights, double learningRate);

    void learn(int maxIter, double minMeanQuadraticError, int indexOfPredictedData, int maxClassificationError);
    virtual map<string, double> checkAccuracy(int tagIndex) = 0;
    virtual string getName() = 0;
    virtual string getResult() = 0;

    vector<Iteration*> getIterations();
    vector<double> getWeights();
    void reset();

protected:
    vector<vector<double>> dataset;
    ActivationFunction* activation;
    vector<double> weights;
    int nbErreurs = 0, iterations = 0;
    double n, result = 0.;

    void addIteration(Iteration* iteration);
    virtual double executeOneIteration(int indexOfPredictedData, bool updateWeights) = 0;


private:
    vector<Iteration*> iterationsSaved;
};



#endif // LEARNINGMODEL_H
