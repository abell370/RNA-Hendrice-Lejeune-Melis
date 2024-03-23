#ifndef LAYER_H
#define LAYER_H
#include <string>
#include <vector>

#include "learningmodel.h"

using namespace std;

class Layer
{

public:
    Layer(vector<vector<double>> dataset, int modelIndex, int amountOfNeurons, double learningRate);
    ~Layer();

    void learn(int maxIter, double minMeanQuadraticError);
    string getResult();
    void reset();

private:
    double learningRate;
    vector<vector<double>> dataset;
    vector<LearningModel*> neurons;

    vector<double> generateWeightVector(int size, bool randomised);

};


#endif // LAYER_H
