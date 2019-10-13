#include <cmath>
#include <vector>

using namespace std;

#ifndef FITNESSFUNCTION_H
#define FITNESSFUNCTION_H

class FitnessFunction
{
public:
    virtual double evaluate(vector<double>) = 0;
};

#endif

#ifndef MICHALEWICZFUNCTION_H
#define MICHALEWICZFUNCTION_H

class MichalewiczFuncion : public FitnessFunction
{
public:
    double evaluate(vector<double> elements)
    {
        double outcome = 0;
        double sum = 0;
        double m = 10;

        for (int i = 0; i < elements.size(); i++)
        {
            sum += sin(elements[i]) * pow(sin(((i + 1) * pow(elements[i], 2)) / M_PI), 2 * m);
        }

        outcome = -sum;

        return outcome;
    };
};

#endif
