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

    int getNum() {
        return 42;
    }

    int getDoubleNum(int n) {
        return n*2;
    }

    char* greet(const char* name) {
        vector<double> elements {2.20, 1.57};
        Individual *individual = new Individual(elements);
        double outcome = individual->evaluate(new MichalewiczFuncion);

        char *greeting = (char *) malloc(50);
        sprintf(greeting, "%s, meet Cpp! %.2f \n", name, outcome);

        return greeting;
    }
}
