config.h
extern const int MAX_VALUE;
extern int globalVar;

file1.c
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

file2.c
#include <stdio.h>
#include "config.h"
extern void updateLocalVar();
extern int getLocalVar();
int main() {
    printf("MAX_VALUE: %d\n", MAX_VALUE);
    printf("Initial globalVar: %d\n", globalVar);
    printf("Initial localVar: %d\n", getLocalVar());

    globalVar += 5;
    updateLocalVar();
    updateLocalVar();

    printf("After update:\n");
    printf("MAX_VALUE: %d\n", MAX_VALUE);
    printf("Updated globalVar: %d\n", globalVar);
    printf("Updated localVar: %d\n", getLocalVar());
    return 0;
}