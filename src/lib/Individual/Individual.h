#include <string>
#include <vector>

#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "../FitnessFunctions/FitnessFunction.cpp"

using namespace std;

class Individual
{
private:
    double fitness;
    int dimensions;
    vector<double> elements;
public:
    Individual(vector<double> elements);
    ~Individual();

    vector<double> getElements();
    void setElements(vector<double> elements);

    double getFitness();

    int getDimensions();

    double evaluate(shared_ptr<FitnessFunction>);

    string toString();
};

#endif
