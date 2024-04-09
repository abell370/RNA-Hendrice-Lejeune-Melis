#include "simpleperceptron.h"

#include <math.h>
#include <iostream>
#include <iterator>     // std::ostream_iterator
#include <vector>       // std::vector
#include <algorithm>    // std::copy
#include <iterator>
using namespace std;



void SimplePerceptron::learn(int maxIter, double minMeanQuadraticError, int indexOfPredictedData, int maxClassificationError) {
    this->reset(); // empty iterations
    if (minMeanQuadraticError != NULL)
    {
        this->loopOnIterations(minMeanQuadraticError, maxIter, indexOfPredictedData);
    }
    else
    {
        this->loopWhileErrorNotNull(maxIter, indexOfPredictedData);
    }
}

void SimplePerceptron::loopOnIterations(float minErrorAccepted, int maxEpoc, int indexOfPredictedData)
{
    for (int i = 1; i <= maxEpoc; i++)
    {
        cout << "Iteration : [" << i << "]" << endl;
        if (this->executeOneIteration(indexOfPredictedData) < minErrorAccepted) break;
        cout << "--------" << endl;
    }
}

void SimplePerceptron::loopWhileErrorNotNull(int maxEpoc, int indexOfPredictedData)
{
    for (int i = 1; i <= maxEpoc; i++)
    {
        cout << "Iteration : [" << i << "]" << endl;
        this->executeOneIteration(indexOfPredictedData);
        if (this->nbErreurs == 0) break;
        cout << "Nb errors [" << this->nbErreurs << "]" << endl;
        cout << "--------" << endl;
    }
}

double SimplePerceptron::executeOneIteration(int indexOfPredictedData)
{
    /*
    Iteration iter = Iteration();
    double errors = 0.0;
    nbErreurs = 0;
    size_t K = this->data.size();
    cout << "Weights used : " << endl;
    copy(begin(this->weights), end(this->weights), ostream_iterator<float>(cout, ", "));
    cout << "" << endl;
    for (uint k = 0; k < K; k++) {
        double y = 0;
        int s = 0;
        for (uint j = 0; j < this->weights.size(); j++) {
            y += this->weights[j] * this->data[k][j];
        }
        int d = this->data[k][this->weights.size()];
        double e = d - y;
        // seuillage
        s = (y >= 0) ? 1 : -1;
        // incr�mentation du nombre d'erreur SI erreur commise
        //if (d != s) nbErreurs++;
        if (d != s) iter.incrementError();
        // correction des poids wi
        for (uint w = 0; w < this->weights.size(); w++) {
            this->weights[w] += this->n * e * this->data[k][w];
        }

        iter.addStep({
            k,
            std::vector<double>(this->weights),
            this->data[k],
            (double)y,
            (double)d,
            (double)e
            });
    }
    // calcul erreur quadratique moyenne
    for (uint k = 0; k < K; k++)
    {
        double y = 0.0;
        for (uint j = 0; j < this->weights.size(); j++)
        {
            y += this->weights[j] * this->data[k][j];
        }
        float e = 0.0;
        if (this->data[k][this->weights.size()] != y)
        {
            e = this->data[k][this->weights.size()] - y;
        }
        errors += pow(e, 2);
    }
    double eMeanQuad = 0.5 * (errors / K);
    cout << "Quadratic mean error = " << eMeanQuad << endl;

    this->addIteration(iter);
    return eMeanQuad;
    */
    return 0.0;

}

string SimplePerceptron::getResult()
{
    return "Done";
}

/*
QVector<double> SimplePerceptron::calcGraph(uint iterationIndex, std::vector<double> x1) {
    
        To calc line equation

        w0*x0 + w1*x1 + x2*w2 = 0

        so, for each given x1 we need to find x2

        x2 = (-w0*x0 - w1*x1)/w2
    
    QVector<double> x2 = QVector<double>(x1.size());

    if (iterationIndex < this->getIterations().size()) {
        Iteration iteration = this->getIterations()[iterationIndex];
        Step lastStep = iteration.getSteps()[iteration.getSteps().size() - 1];

        for (unsigned i = 0; i < x1.size(); i++) {
            x2[i] = (-lastStep.weights[0] * 1 - lastStep.weights[1] * x1[i]) / lastStep.weights[2];
        }
    }

    return x2;
}
*/

