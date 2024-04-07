#ifndef LAYER_H
#define LAYER_H
#include <string>
#include <vector>

#include "learningmodel.h"
#include "activationfunction.h"
#include "layeringmodel.h"

using namespace std;

class Layer : public LayeringModel
{
public:
    Layer() {};
    ~Layer() {};

    void setup(vector<vector<double>> dataset, int nbTags, int modelIndex, double learningRate);
    void train(double stopThreadshold, int maxEpoc, ActivationFunction* aFunction, int maxClassificationError);
    void getResult();
    void reset();


private:
    double learningRate = 0.;
    vector<vector<double>> dataset;
    vector<LearningModel*> neurons;

    vector<double> generateWeightVector(int size, bool randomised);

};


#endif // LAYER_H
