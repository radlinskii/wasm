#include <stdio.h>
#include "Population/Population.h"
#include "Parameters/Parameters.h"
#include "DifferentialEvolution/DifferentialEvolution.h"
#include "Individual/Individual.h"
#include "FitnessFunctions/MichalewiczFunction.cpp"
#include "FitnessFunctions/SphereFunction.cpp"
#include "FitnessFunctions/BealeFunction.cpp"

vector<vector<double>> zip(double* array, int len, int zipLen) {
    vector<vector<double>> vector2d;
    for(int i = 0, count = 0; i < len; i++) {
        vector<double> v;
        for (int j = 0; j < zipLen; j++) {
            v.push_back(array[count]);
            count++;
        }
        vector2d.push_back(v);
    }

    return vector2d;
}

char* calculate(double* elements, int len, int dimensions, FitnessFunction* f) {
    int populationLen = len / dimensions;

    vector<vector<double>> zippedVectors = zip(elements, populationLen, dimensions);

    Population* pop = new Population(zippedVectors);
    Parameters* params = new Parameters();

    params->setMaxNumOfGenerations(100);
    params->setFitnessFunction(f);
    params->setAgentCount(populationLen);

    DifferentialEvolution* de = new DifferentialEvolution(params);
    de->setPopulation(pop);

    Individual* solution = de->evaluate();

    char* greeting = (char*) malloc(70);
    sprintf(greeting, "Solution is: %s, with result: %.4f\n", solution->toString().c_str(), solution->getFitness());

    return greeting;
}

using namespace std;
extern "C" {
    int main() {
        printf("main.cpp initialized!\n");

        return 0;
    }

    char* greet(char* name) {
        char* greeting = (char*) malloc(50);
        sprintf(greeting, "%s, meet C++!\n", name);

        return greeting;
    }

    char* calcSphere(double* elements, int len, int dimensions, double minValue, double maxValue) {
        FitnessFunction* f = new SphereFunction(dimensions, make_tuple(minValue, maxValue));

        return calculate(elements, len, dimensions, f);
    }

    char* calcMichalewicz(double* elements, int len, int dimensions, double minValue, double maxValue) {
        FitnessFunction* f = new MichalewiczFunction(dimensions, make_tuple(minValue, maxValue));

        return calculate(elements, len, dimensions, f);
    }

    char* calcBeale(double* elements, int len, int dimensions, double minValue, double maxValue) {
        FitnessFunction* f = new BealeFunction(dimensions, make_tuple(minValue, maxValue));

        return calculate(elements, len, dimensions, f);
    }
}
