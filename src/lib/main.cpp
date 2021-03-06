#include <stdio.h>
#include "Population/Population.h"
#include "Parameters/Parameters.h"
#include "DifferentialEvolution/DifferentialEvolution.h"
#include "Individual/Individual.h"
#include "FitnessFunctions/SphereFunction.cpp"
#include "FitnessFunctions/SalomonFunction.cpp"
#include "FitnessFunctions/RastriginFunction.cpp"
#include "FitnessFunctions/RosenbrockFunction.cpp"
#include "FitnessFunctions/AckleyFunction.cpp"

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

double* calculate(double* elements, int len, shared_ptr<FitnessFunction> f, double CR, double F, int maxNumOfGenerations) {
    int populationLen = len / f->getDimensions();

    vector<vector<double>> zippedVectors = zip(elements, populationLen, f->getDimensions());

    shared_ptr<Population> pop = make_shared<Population>(zippedVectors);
    shared_ptr<Parameters> params = make_shared<Parameters>();

    params->setFitnessFunction(f);
    params->setPopulationLength(populationLen);
    params->setCR(CR);
    params->setF(F);
    params->setMaxNumOfGenerations(maxNumOfGenerations);

    unique_ptr<DifferentialEvolution> de = make_unique<DifferentialEvolution>(params);
    de->setPopulation(pop);

    shared_ptr<Population> evaluatedPopulation = de->evaluate();

    vector<vector<double>> vector2d = evaluatedPopulation->toVectors();

    vector<double> flat = flatten(vector2d, f->getDimensions());
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

    double* calcSphere(double* elements, int len, int dimensions, double min, double max, double CR, double F, int maxNumOfGenerations) {
        shared_ptr<FitnessFunction> f = make_shared<SphereFunction>(dimensions, make_tuple(min, max));

        return calculate(elements, len, f, CR, F, maxNumOfGenerations);
    }

    double* calcSalomon(double* elements, int len, int dimensions, double min, double max, double CR, double F, int maxNumOfGenerations) {
        shared_ptr<FitnessFunction> f = make_shared<SalomonFunction>(dimensions, make_tuple(min, max));

        return calculate(elements, len, f, CR, F, maxNumOfGenerations);
    }

    double* calcRastrigin(double* elements, int len, int dimensions, double min, double max, double CR, double F, int maxNumOfGenerations) {
        shared_ptr<FitnessFunction> f = make_shared<RastriginFunction>(dimensions, make_tuple(min, max));

        return calculate(elements, len, f, CR, F, maxNumOfGenerations);
    }

    double* calcRosenbrock(double* elements, int len, int dimensions, double min, double max, double CR, double F, int maxNumOfGenerations) {
        shared_ptr<FitnessFunction> f = make_shared<RosenbrockFunction>(dimensions, make_tuple(min, max));

        return calculate(elements, len, f, CR, F, maxNumOfGenerations);
    }

    double* calcAckley(double* elements, int len, int dimensions, double min, double max, double CR, double F, int maxNumOfGenerations) {
        shared_ptr<FitnessFunction> f = make_shared<AckleyFunction>(dimensions, make_tuple(min, max));

        return calculate(elements, len, f, CR, F, maxNumOfGenerations);
    }
}
