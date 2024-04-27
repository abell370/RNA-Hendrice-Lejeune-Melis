#include "simpleperceptron.h"

#include <math.h>
#include <iostream>
#include <iterator>     // std::ostream_iterator
#include <vector>       // std::vector
#include <algorithm>    // std::copy
#include <iterator>
using namespace std;

map<string, double> SimplePerceptron::checkAccuracy(int tagIndex)
{
    this->nbErreurs = 0;
    this->iterations = 0;
    double E = this->executeOneIteration(tagIndex, false);
    return {
        {"nbErreurs", this->nbErreurs},
        {"eMoy", -1},
        {"nbIteration", this->iterations}
    };
}

void SimplePerceptron::learn(int maxIter, double minMeanQuadraticError, int indexOfPredictedData, int maxClassificationError) {
    {
        this->loopWhileErrorNotNull(indexOfPredictedData);
    }
}

void SimplePerceptron::loopWhileErrorNotNull(int indexOfPredictedData)
{
    int i = 0;
    do
    {
        i++;
        cout << "Iteration : [" << i << "]" << endl;
        this->executeOneIteration(indexOfPredictedData, true); //true ?
        cout << "Nb errors [" << this->nbErreurs << "]" << endl;
        cout << "--------" << endl;
    } 
    // nbErreur = 0 ?
    // si oui, fin apprentissage
    // si non, on recommence
    while (nbErreurs != 0);
    this->iterations = i;
}

int SimplePerceptron::executeOneIteration(int indexOfPredicted, bool updateWeights)
{
    //initialisation nbErreurs
	this->nbErreurs = 0;
    //pour chaque exemple
    for (uint k = 0; k < this->dataset.size(); k++)
    {
        int p = this->weights[0]; // multiplié par 1
        for (int x = 1; x < this->weights.size(); x++)
        {
            p += this->weights[x] * this->dataset[k][x - 1];
        }
        // evaluation sortie perceptron
        int y = activation->compute(p);
        int s = activation->performThresholding(y);
        // calcul de l'erreur 
        // erreur = etiquette - sortie
        int e = this->dataset[k][indexOfPredicted] - s; 
        // erreur = 0 ?
        // si oui
        //  k [+1]
        // si non
        //  correction des poids + nbErreur++ 
        //  k [+1]
        if (e != 0)
        {
            this->weights[0] += weights[0] + this->n * e * 1.;
            for (int i = 1; i < this->weights.size(); i++)
            {
                this->weights[i] = this->weights[i] + this->n * e * this->dataset[k][i - 1];
            }
            this->nbErreurs++;
        }
    }
    return 0;
}

string SimplePerceptron::getResult()
{
    return "nbIter= " + to_string(this->iterations);
}
