#pragma once
#include "layerbuilder.h"
class ConcretLayerBuilder :
    public LayerBuilder
{
public:
    ConcretLayerBuilder() {};
    ~ConcretLayerBuilder() {};

    void SetDataSet(vector<vector<double>> dataset) const override;
    void SetTypeOfLearningModel(int model) const override;
    void SetNumberOfClasses(int amountofneurons) const override;
    void SetLearningRate(double learningrate)const override;
    void SetNumberOfEntries(int nbentries) const override;
};

