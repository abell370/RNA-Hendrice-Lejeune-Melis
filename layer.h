#ifndef LAYER_H
#define LAYER_H
#include <string>
#include <vector>

#include "learningmodel.h"
#include "activationfunction.h"
#include "layeringmodel.h"

using namespace std;

class MonoLayer 
    : public LayeringModel
{
public:
    using LayeringModel::LayeringModel;

    void setup(int nbTags, int modelIndex, double learningRate, bool randomNormalWeights);
    History* train(double stopThreadshold, int maxEpoc, int maxClassificationError);
    map<string, double> checkAccuracy(vector<vector<double>> validationDataset);
    vector<double> getResult();
    void reset();

    vector<vector<double>> getDecisionWeights();

private:
    double learningRate = 0.;
    vector<LearningModel*> neurons;

    vector<double> generateWeightVector(int size, bool randomised);

};


#endif // LAYER_H
