#include <stdio.h>
//#include "file1.c"
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