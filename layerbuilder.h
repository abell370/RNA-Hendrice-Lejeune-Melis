#pragma once

#include <vector>

using namespace std;

class LayerBuilder {
public:
    virtual ~LayerBuilder() {}
    virtual void SetDataSet(vector<vector<double>> dataset) const = 0;
    virtual void SetTypeOfLearningModel(int model) const  = 0;
    virtual void SetNumberOfClasses(int amountofneurons) const  = 0;
    virtual void SetLearningRate(double learningrate) const = 0;
    virtual void SetNumberOfEntries(int nbentries) const = 0;
};