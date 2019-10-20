#include "./FitnessFunction.cpp"

#ifndef MICHALEWICZ_FUNCTION_H
#define MICHALEWICZ_FUNCTION_H

// min is at  f(2.20, 1.57) = -1.8013
class MichalewiczFunction : public FitnessFunction {
public:
    MichalewiczFunction() {
        this->domain = make_tuple(0, M_PI);
        this->dimensions = 2;
    }

    MichalewiczFunction(int dimensions, tuple<double, double> domain) {
        this->dimensions = dimensions;
        this->domain = domain;
    }

    double evaluate(vector<double> elements) {
        double outcome = 0;
        double sum = 0;
        double m = 10;

        for (int i = 0; i < elements.size(); i++) {
            sum += sin(elements[i]) * pow(sin(((i + 1) * pow(elements[i], 2)) / M_PI), 2 * m);
        }

        outcome = -sum;

        return outcome;
    };
};

#endif
