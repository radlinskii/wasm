#include "./FitnessFunction.cpp"

#ifndef MICHALEWICZ_FUNCTION_H
#define MICHALEWICZ_FUNCTION_H

// dimensions: 2
// bounds: 0, M_PI
// min is at  f(2.20, 1.57) = -1.8013
class MichalewiczFunction : public FitnessFunction {
public:
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
