#ifndef LAYER_H
#define LAYER_H
#include <string>
#include <vector>

#include "learningmodel.h"
#include "activationfunction.h"
#include "layeringmodel.h"

using namespace std;

/*
    Classe repr�sentant la seule couche du mod�le mono-couche. Elle contient les diff�rents neurones qui apprennent s�paremment les uns des autres.
*/
class MonoLayer 
    : public LayeringModel
{
public:
    using LayeringModel::LayeringModel;

    void setup(int nbTags, int modelIndex, double learningRate, bool randomNormalWeights);
    History* train(double stopThreadshold, int maxEpoc, int maxClassificationError);
    map<string, double> checkAccuracy(vector<vector<double>> validationDataset);
    void reset();

    vector<vector<double>> getDecisionWeights();
    vector<double> predict(vector<double> input);

private:
    double learningRate = 0.;
    vector<LearningModel*> neurons;

    vector<double> generateWeightVector(int size, bool randomised);

};


#endif // LAYER_H
