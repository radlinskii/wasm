#include <emscripten.h>
#include <stdio.h>
#include <string.h>

int main() {
    printf("Hello from WebAssembly!\n");

    char * name = "'ignacy'";
    char script[50];

    sprintf(script, "greetFromJS(%s", name);

    char * string = emscripten_run_script_string("greetFromJS('ignacy')");

    printf("%s\n", string);

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
    sprintf(greeting, "Hello %s, from C!\n", name);

    return greeting;
}
