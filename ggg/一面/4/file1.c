#include "config.h"
const int MAX_VALUE = 100;
static int localVar = 5;
int globalVar = 10;

void updateLocalVar() {
    static int counter = 0;
    counter++;
    localVar += counter;
}
int getLocalVar() {
    return localVar;
}