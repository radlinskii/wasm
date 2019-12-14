#include "./FitnessFunction.cpp"

#ifndef ACKLEY_FUNCTION_H
#define ACKLEY_FUNCTION_H

// min is at  f(0, ..., 0) = 0
class AckleyFunction : public FitnessFunction {
public:
    AckleyFunction() {
        this->domain = make_tuple(-32, 32);
        this->dimensions = 50;
    }

    AckleyFunction(int dimensions, tuple<double, double> domain) {
        this->dimensions = dimensions;
        this->domain = domain;
    }

    double evaluate(vector<double> elements) {
        double sum1 = 0.0;
        double sum2 = 0.0;

        for(int i = dimensions - 1; i >= 0; i--) {
            sum1 += (elements[i] * elements[i]);
            sum2 += cos(2.0 * M_PI * elements[i]);
        }

        return -20.0 * exp(-0.2 * sqrt(sum1 / dimensions)) - exp(sum2 / dimensions) + 20.0 + exp(1);
    };
};

#endif
