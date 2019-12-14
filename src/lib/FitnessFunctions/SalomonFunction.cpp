#include "./FitnessFunction.cpp"

#ifndef SALOMON_FUNCTION_H
#define SALOMON_FUNCTION_H

// min is at  f(0, ..., 0) = 0
class SalomonFunction : public FitnessFunction {
public:
    SalomonFunction() {
        this->domain = make_tuple(-100, 100);
        this->dimensions = 50;
    }

    SalomonFunction(int dimensions, tuple<double, double> domain) {
        this->dimensions = dimensions;
        this->domain = domain;
    }

    double evaluate(vector<double> elements) {
        double squareSum = 0.0;

        for(int i=0; i<dimensions; i++) {
            squareSum += pow(elements[i], 2);
        }

        double sqrtSqaureSum = sqrt(squareSum);

        return 1 - cos(2 * M_PI * sqrtSqaureSum) + 0.1 * sqrtSqaureSum;
    };
};

#endif
