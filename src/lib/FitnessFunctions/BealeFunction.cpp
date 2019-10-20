#include "./FitnessFunction.cpp"

#ifndef BEALE_FUNCTION_H
#define BEALE_FUNCTION_H

// min at  f(3, 0.5) = 0
class BealeFunction : public FitnessFunction {
public:
    BealeFunction() {
        this->domain = make_tuple(-4.5, 4.5);
        this->dimensions = 2;
    }

    BealeFunction(int dimensions, tuple<double, double> domain) {
        this->dimensions = dimensions;
        this->domain = domain;
    }

    double evaluate(vector<double> elements) {
        double x1 = pow(1.5 - elements[0] + (elements[0]*elements[1]), 2);
        double x2 = pow(2.25 - elements[0] + (elements[0]*pow(elements[1], 2)), 2);
        double x3 = pow(2.625 - elements[0] + (elements[0]*pow(elements[1], 3)), 2);

        return x1 + x2 + x3;
    };
};

#endif
