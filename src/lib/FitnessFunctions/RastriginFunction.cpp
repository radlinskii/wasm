#include "./FitnessFunction.cpp"

#ifndef RASTRIGIN_FUNCTION_H
#define RASTRIGIN_FUNCTION_H

// min is at  f(0, ..., 0) = 0
class RastriginFunction : public FitnessFunction {
public:
    RastriginFunction() {
        this->domain = make_tuple(-100, 100);
        this->dimensions = 50;
    }

    RastriginFunction(int dimensions, tuple<double, double> domain) {
        this->dimensions = dimensions;
        this->domain = domain;
    }

    double evaluate(vector<double> elements) {
        double result = 0.0;

        for(int i = dimensions - 1; i >= 0; i--) {
            result += elements[i] * elements[i] - 10.0 * cos(2 * M_PI * elements[i]) + 10.0;
        }

        return result;
    };
};

#endif
