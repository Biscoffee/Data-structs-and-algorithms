#include <stdio.h>
#define INT_STR int*
typedef int* int_str;
 typedef struct str {
     short e1;
     int e2;
     char e3[3];
     INT_STR iptr1, iptr2;
     double e5;
     int e6;
}str;
typedef union uni {
    short e1;
    int e2;
    char e3[6];
    struct str e4;
    double e5;
    int e6;
}uni;
int main(){
    int x = sizeof(str);
    int y = sizeof(uni);
    printf("x = %d, y = %d\n", x,y);
    printf("hello = %d\n", printf("3G = %d \n",--x == 39 && x-- == 47 && ++y == 49));
    printf("x1 = %d, y1 = %d\n", x,y);
    return 0;
 }