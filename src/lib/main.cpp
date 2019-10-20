#include <stdio.h>
#include "Population/Population.h"
#include "Parameters/Parameters.h"
#include "DifferentialEvolution/DifferentialEvolution.h"
#include "Individual/Individual.h"
#include "FitnessFunctions/MichalewiczFunction.cpp"
#include "FitnessFunctions/SphereFunction.cpp"
#include "FitnessFunctions/BealeFunction.cpp"

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

    char* calculate(double* elements, int len) {
        Parameters* params = new Parameters();
        params->setMaxNumOfIterations(100);
        params->setDimensions(2);
        params->setDomain(make_tuple(0, M_PI));
        params->setFitnessFunction(new MichalewiczFunction());

        DifferentialEvolution* de = new DifferentialEvolution(params);
        de->evaluate();

        char* greeting = (char*) malloc(50);
        sprintf(greeting, "Calculating...\n");

        return greeting;
    }
}
