#include "./FitnessFunction.cpp"

#ifndef ROSENBROCK_FUNCTION_H
#define ROSENBROCK_FUNCTION_H

// min is at  f(0, ..., 0) = 0
class RosenbrockFunction : public FitnessFunction {
public:
    RosenbrockFunction() {
        this->domain = make_tuple(-100, 100);
        this->dimensions = 50;
    }

    RosenbrockFunction(int dimensions, tuple<double, double> domain) {
        this->dimensions = dimensions;
        this->domain = domain;
    }

    double evaluate(vector<double> elements) {
        double tmp;
        double result = 0.0;

        for (int j = dimensions-1; j >= 0; j--) {
            tmp = (elements[j] * elements[j]) - elements[j + 1];
            result += 100.0 * tmp * tmp;
            tmp  = elements[j] - 1.0;
            result += tmp * tmp;
        }

        return result;
    };
};

#endif
