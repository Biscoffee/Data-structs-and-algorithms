#include <stdio.h>
#include <string.h>

int calc_length(int num1, char op, int num2, int result) {

    char equation[50];
    snprintf(equation, sizeof(equation), "%d%c%d=%d", num1, op, num2, result);
    return strlen(equation);
}

int main() {
    int i;  
    scanf("%d", &i);

    char prev_op = 0;  
    for (int j = 0; j < i; j++) {
        char op;     
        int num1, num2;

        if (scanf(" %c", &op) == 1 && (op == 'a' || op == 'b' || op == 'c')) {

            scanf("%d %d", &num1, &num2);
            prev_op = op; 
        } else {

            ungetc(op, stdin);  
            scanf("%d %d", &num1, &num2);
            op = prev_op;  
        }

        int result;
        char symbol;
        if (op == 'a') {
            result = num1 + num2;
            symbol = '+';
        } else if (op == 'b') {
            result = num1 - num2;
            symbol = '-';
        } else if (op == 'c') {
            result = num1 * num2;
            symbol = '*';
        }

        printf("%d%c%d=%d\n", num1, symbol, num2, result);
        printf("%d\n", calc_length(num1, symbol, num2, result));
    }

    return 0;
}