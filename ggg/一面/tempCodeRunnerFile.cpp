#include <stdio.h>
int main() {
    unsigned short a = 10, b = 5;
    while (a - b >= 0) {  
        printf("%d ", a);
        a -= 3;
    }
    return 0;
}