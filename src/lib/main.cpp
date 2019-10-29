#include <stdio.h>
#include "Population/Population.h"
#include "Parameters/Parameters.h"
#include "DifferentialEvolution/DifferentialEvolution.h"
#include "Individual/Individual.h"
#include "FitnessFunctions/MichalewiczFunction.cpp"
#include "FitnessFunctions/SphereFunction.cpp"
#include "FitnessFunctions/BealeFunction.cpp"

using namespace std;

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

vector<double> flatten(vector<vector<double>> v, int flattenLen) {
    vector<double> flat;
    for(int i = 0; i < v.size(); i++) {
        for (int j = 0; j < flattenLen; j++) {
            flat.push_back(v[i][j]);
        }
    }

    return flat;
}

double* calculate(double* elements, int len, int dimensions, FitnessFunction* f) {
    int populationLen = len / dimensions;

    vector<vector<double>> zippedVectors = zip(elements, populationLen, dimensions);

    Population* pop = new Population(zippedVectors);
    Parameters* params = new Parameters();

    params->setMaxNumOfGenerations(100);
    params->setFitnessFunction(f);
    params->setAgentCount(populationLen);

    DifferentialEvolution* de = new DifferentialEvolution(params);
    de->setPopulation(pop);

    Population* solution = de->evaluate();

    vector<vector<double>> vector2d = solution->toVectors();

    vector<double> flat = flatten(vector2d, dimensions);
    double* result = new double[len];
    copy(flat.begin(), flat.end(), result);

    return result;
}

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

    double* calcSphere(double* elements, int len, int dimensions, double minValue, double maxValue) {
        FitnessFunction* f = new SphereFunction(dimensions, make_tuple(minValue, maxValue));

        return calculate(elements, len, dimensions, f);
    }

    double* calcMichalewicz(double* elements, int len, int dimensions, double minValue, double maxValue) {
        FitnessFunction* f = new MichalewiczFunction(dimensions, make_tuple(minValue, maxValue));

        return calculate(elements, len, dimensions, f);
    }

    double* calcBeale(double* elements, int len, int dimensions, double minValue, double maxValue) {
        FitnessFunction* f = new BealeFunction(dimensions, make_tuple(minValue, maxValue));

        return calculate(elements, len, dimensions, f);
    }
}
