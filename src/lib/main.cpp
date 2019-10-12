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

    char* greet(char* name) {
        list<double> elements {1, 2, 3, 4};
        Individual *individual = new Individual(elements);

        char *greeting = (char *) malloc(50);
        sprintf(greeting, "%s, meet Cpp!\n", individual->to_string().c_str());

        return greeting;
    }
}
