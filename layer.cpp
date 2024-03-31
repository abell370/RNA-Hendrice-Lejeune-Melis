#include "layer.h"
#include "learningmodelfactory.h"

Layer::Layer(vector<vector<double>> dataset, int modelIndex, int amountOfNeurons, double learningRate, int nbEntry) : dataset(dataset), learningRate(learningRate)
{
    for (int i = 0; i < amountOfNeurons; i++)
    {
        LearningModel* neuron = LearningModelFactory::create(modelIndex);
        neuron->setup(dataset, this->generateWeightVector(nbEntry + 1, false), learningRate);
        this->neurons.push_back(neuron);
    }
}

vector<double> Layer::generateWeightVector(int size, bool randomised)
{
    vector<double> wVector(size);
    return wVector;
}


void Layer::learn(int maxIter, double minMeanQuadraticError)
{
    for (int i = 0; i < this->neurons.size(); i++)
    {
        /*
            Si une ligne == 15 �l�ments
            Qu'on se base sur le fait que les �tiquettes sont toujours en fin de ligne (position 12 => classe 1, 13 => classe 2, 14 => classe 3)
            S'il y a 3 �tiquettes par lignes
            Les lignes sont mises par ordre croissant (classe 1, classe 2, classe 3)

                                            nb �l�ments - ( nb neurones - i )
            Neurone 1 => ligne[predictedData] = 15 - ( 3 - 0 ) = 12
            Neurone 2 => ligne[predictedData] = 15 - ( 3 - 1 ) = 13
            Neurone 3 => ligne[predictedData] = 15 - ( 3 - 2 ) = 14

        */
        int indexOfPredictedOutput = this->dataset[0].size() - (this->neurons.size() - i);
        this->neurons[i]->learn(maxIter, minMeanQuadraticError, indexOfPredictedOutput);
    }
}

string Layer::getResult()
{
    string result = "";
    for (int i = 0; i < this->neurons.size(); i++)
    {
        int index = i + 1; // Remove the unnecessary addition
        // Convert integers to strings before concatenating
        result += "\nClasse " + to_string(index) + " => Result " + this->neurons[i]->getResult();
    }
    return result;
}

void Layer::reset()
{
    for (LearningModel* model : this->neurons)
    {
        model->reset();
    }
}

