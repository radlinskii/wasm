/*
def func2(x):
    # Beale's function, use bounds=[(-4.5, 4.5),(-4.5, 4.5)], f(3,0.5)=0.
    term1 = (1.500 - x[0] + x[0]*x[1])**2
    term2 = (2.250 - x[0] + x[0]*x[1]**2)**2
    term3 = (2.625 - x[0] + x[0]*x[1]**3)**2
    return term1 + term2 + term3
*/

#include "./FitnessFunction.cpp"

#ifndef BEALE_FUNCTION_H
#define BEALE_FUNCTION_H

// dimensions: 2
// bounds: -4.5, 4.5
// min at  f(3, 0.5) = 0
class BealeFunction : public FitnessFunction {
public:
    double evaluate(vector<double> elements) {
        double x1 = pow(1.5 - elements[0] + (elements[0]*elements[1]), 2);
        double x2 = pow(2.25 - elements[0] + (elements[0]*pow(elements[1], 2)), 2);
        double x3 = pow(2.625 - elements[0] + (elements[0]*pow(elements[1], 3)), 2);

        return x1 + x2 + x3;
    };
};

#endif
