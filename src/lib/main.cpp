#include <emscripten.h>
#include <stdio.h>
#include <string.h>

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

    char * greet(char * name) {
        char greeting[50];
        sprintf(greeting, "%s, meet C++!\n", name);

        return greeting;
    }
}
