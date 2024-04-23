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

    map<string, double> getData();
    void setLabel(string label);

};

