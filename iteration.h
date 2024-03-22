#ifndef ITERATION_H
#define ITERATION_H

#include <vector>
#include <QVector>

struct Step {
    uint k;
    std::vector<double> weights;
    std::vector<double> entries;
    double y, d, e;
};

class Iteration
{
private:
    unsigned int errorNb;
    std::vector<Step> steps;
public:
    Iteration() : errorNb(0) {};

    int getErrorNb() { return this->errorNb; }
    std::vector<Step> getSteps() { return std::vector<Step>(this->steps); }

    void addStep(Step step) { this->steps.push_back(step); };
    void incrementError() { this->errorNb++; }
};

#endif // ITERATION_H
