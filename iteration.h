#pragma once

#include <vector>
#include <map>
#include <string>

using namespace std;


class Iteration
{
private:
    unsigned int classificationError = 0;
    double eMoy = 0.;
    string label = "";
public:
    Iteration(int classificationE, double eMoy) {
        this->classificationError = classificationE;
        this->eMoy = eMoy;
    };

    inline string getLabel() { return this->label; };
    inline double getMSE() { return this->eMoy; }
    inline int getClassificationE() { return this->classificationError; };
    inline void setLabel(string label) { this->label = label; };

};

