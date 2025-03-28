#include <stdio.h>
#include <stdlib.h>
int main(int argc, const char * argv[]) {
    short grid[3][3] = {{10,20,30},{40,50,60},{70,80,90}};
    char *pc = (char*)grid + 3 * sizeof(short);
    short (*ptr1)[2] = (short(*)[2])grid[1];
    short *ptr2 = (short*)(grid + 1);
    printf("1.%d\n", *(short*)(pc - sizeof(short)*2));
    printf("2.%d\n", *ptr2 + 1);
    printf("3.%d\n", *(ptr2 + 1));
    printf("4.%d\n", **(grid + 2));                  
    printf("5.%d\n", **(ptr1 + 2));
    printf("6.%d\n", *(*ptr1 + 2));
    printf("7.%d\n", (*(grid+1))[-1]);
    printf("8.%d\n", *(short *)(pc - sizeof(char) * 2));
return 0;}