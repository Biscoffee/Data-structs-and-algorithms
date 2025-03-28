#include <stdio.h>
#define SQUARE(x) (x * x)
#define MAX(A, B) (A > B ? A : B)
int square(int x) {
    return x * x;
}
int max(int a, int b) {
    return a > b ? a : b;
}
int main() {
    int a = 5;
    int b = 10;
    int result1 = SQUARE(a + 1);
    int result2 = square(a + 1);
    printf("result1 = %d, result2 = %d\n", result1, result2);

    int result3 = MAX(a++, b++);
    int result4 = max(a++, b++);
    printf("result3 = %d, result4 = %d\n", result3, result4);
    printf("a = %d, b = %d\n", a, b);

    int result5 = SQUARE(++a);
    int result6 = square(++a);
    printf("result5 = %d, result6 = %d\n", result5, result6);
    printf("a = %d\n", a);

    return 0;}