#include <cmath>
#include <vector>

using namespace std;

#ifndef FITNESS_FUNCTION_H
#define FITNESS_FUNCTION_H

class FitnessFunction {
public:
    virtual double evaluate(vector<double>) = 0;
};

#endif
