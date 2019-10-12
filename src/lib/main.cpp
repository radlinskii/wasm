#include <stdio.h>
#include <string.h>
#include <sstream>
#include "Individual.h"

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
        Individual *individual = new Individual(name);
        char *greeting = (char *) malloc(50);
        sprintf(greeting, "%s, meet Cpp!\n", individual->getName());

        return greeting;
    }
}
