#include "./FitnessFunction.cpp"

#ifndef SPHERE_FUNCTION_H
#define SPHERE_FUNCTION_H

// min is at  f(0, ..., 0) = 0
class SphereFunction : public FitnessFunction {
public:
    SphereFunction() {
        this->domain = make_tuple(-100, 100);
        this->dimensions = 4;
    }

    SphereFunction(int dimensions, tuple<double, double> domain) {
        this->dimensions = dimensions;
        this->domain = domain;
    }

    double evaluate(vector<double> elements) {
        double sum = 0;

        for (double x : elements) {
            sum += pow(x, 2);
        }

        return sum;
    };
};

#endif
