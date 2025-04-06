#include <stdio.h>

#define MAX_R 1000

int triangle[MAX_R][MAX_R];
int dp[MAX_R];

int main() {
    int r;
    scanf("%d", &r);

    for (int i = 0; i < r; i++) {
        for (int j = 0; j <= i; j++) {
            scanf("%d", &triangle[i][j]);
        }
    }

    for (int j = 0; j < r; j++) {
        dp[j] = triangle[r-1][j];
    }

    for (int i = r - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            dp[j] = triangle[i][j] + (dp[j] > dp[j + 1] ? dp[j] : dp[j + 1]);
        }
    }

    printf("%d\n", dp[0]);
    return 0;
}