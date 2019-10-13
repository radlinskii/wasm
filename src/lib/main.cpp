#include <stdio.h>
#include <string.h>
#include <sstream>
#include "Individual/Individual.h"

using namespace std;
extern "C" {
    int main() {
        printf("main.cpp initialized!\n");

        return 0;
    }

    char* greet(char *name) {
        char *greeting = (char *) malloc(50);
        sprintf(greeting, "%s, meet C++!\n", name);

        return greeting;
    }

    char* calculate(double *elements, int len) {
        vector<double> elementsVector;

        for (int i = 0; i < len; i++) {
            elementsVector.push_back(elements[i]);
        }

        Individual *individual = new Individual(elementsVector);
        double outcome = individual->evaluate(new MichalewiczFuncion);

        char *greeting = (char *) malloc(50);
        sprintf(greeting, "calculation result: %f \n", outcome);

        return greeting;
    }
}
