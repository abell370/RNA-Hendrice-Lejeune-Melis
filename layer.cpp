﻿#include "layer.h"
#include "learningmodelfactory.h"
#include "activationfunction.h"
#include "identityactivation.h"
#include "utils.h"


map<string, double> MonoLayer::checkAccuracy(vector<vector<double>> validationDataset)
{
    this->dataset = dataset;
    map<string, double> results;
    for (int i = 0; i < this->neurons.size(); i++)
    {
        int indexOfPredictedOutput = this->dataset[0].size() - (this->neurons.size() - i);
        // TODO utiliser le paramètre activation
        map<string, double> result = this->neurons[i]->checkAccuracy(indexOfPredictedOutput);
        for (const auto& [key, value] : result)
            results.insert({ "["+to_string(i) + "] " + key, value} );
    }
    return results;
}

vector<double> MonoLayer::generateWeightVector(int size, bool randomised)
{
    vector<double> wVector(size);

    if (randomised) {
        wVector = Utils::generateRandom(size);
    }

    return wVector;
}

void MonoLayer::setup(int nbTags, int modelIndex, double learningRate)
{
    if (nbTags == 2)
    {
        nbTags = 1;
    }
    int nbEntry = dataset[0].size() - nbTags;
    for (int i = 0; i < nbTags; i++)
    {
        vector<double> weights = this->generateWeightVector(nbEntry + 1, false);
        LearningModel* neuron = LearningModelFactory::create(modelIndex, dataset, weights, learningRate,aFunction);
        neurons.push_back(neuron);
    }
}


void MonoLayer::train(double stopThreadshold, int maxEpoc, int maxClassificationError)
{
    for (int i = 0; i < this->neurons.size(); i++)
    {
        /*
            Si une ligne == 15 �l�ments
            Qu'on se base sur le fait que les �tiquettes sont toujours en fin de ligne (position 12 => classe 1, 13 => classe 2, 14 => classe 3)
            S'il y a 3 �tiquettes par lignes
            Les lignes sont mises par ordre croissant (classe 1, classe 2, classe 3)

                                            nb elements - ( nb neurones - i )
            Neurone 1 => ligne[predictedData] = 15 - ( 3 - 0 ) = 12
            Neurone 2 => ligne[predictedData] = 15 - ( 3 - 1 ) = 13
            Neurone 3 => ligne[predictedData] = 15 - ( 3 - 2 ) = 14

        */
        int indexOfPredictedOutput = this->dataset[0].size() - (this->neurons.size() - i);
        // TODO utiliser le paramètre activation
        this->neurons[i]->learn(maxEpoc, stopThreadshold, indexOfPredictedOutput, maxClassificationError);
    }
}

void MonoLayer::getResult()
{
    string result = "";
    for (int i = 0; i < this->neurons.size(); i++)
    {
        int index = i + 1; // Remove the unnecessary addition
        // Convert integers to strings before concatenating
        result += "\nClasse " + to_string(index) + " => Result " + this->neurons[i]->getResult();
    };
}

void MonoLayer::reset()
{
    for (LearningModel* model : this->neurons)
    {
        model->reset();
    }
}

