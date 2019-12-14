#include "./FitnessFunction.cpp"

#ifndef ELLIPTIC_FUNCTION_H
#define ELLIPTIC_FUNCTION_H

// min is at  f(0, ..., 0) = 0
class EllipticFunction : public FitnessFunction {
public:
    EllipticFunction() {
        this->domain = make_tuple(-100, 100);
        this->dimensions = 4;
    }

    EllipticFunction(int dimensions, tuple<double, double> domain) {
        this->dimensions = dimensions;
        this->domain = domain;
    }

    double evaluate(vector<double> elements) {
        double result = 0.0;

        for(int i=0; i<dimensions; i++) {
            result += pow(1.0e6,  i/((double)(dimensions - 1)) ) * elements[i] * elements[i];
        }

        return result;
    };
};

#endif
