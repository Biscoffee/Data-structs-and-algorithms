#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10001
int main()
{
    int n, i, j, t = 2;
    int a[40][40] = {0};
    int x = 1, y;
    scanf("%d", &n);
    y = (n + 1) / 2;
    a[x][y] = 1;
    for (i = 2; i <= n*n; i++)
    {
        if (x == 1 && y != n)
        {
            a[n][y + 1] = t;
            x = n;
            y = y + 1;
            t++;
        }
        else if (x != 1 && y == n)
        {
            a[x - 1][1] = t;
            x = x - 1;
            y = 1;
            t++;
        }
        else if (x == 1 && y == n)
        {
            a[x + 1][y] = t;
            x = x + 1;
            y = y;
            t++;
        }
        else if (x != 1 && y != n)
        {
            if (a[x - 1][y + 1] == 0)
            {
                a[x - 1][y + 1] = t;
                x = x - 1;
                y = y + 1;
                t++;
            }
            else
            {
                a[x + 1][y] = t;
                x = x + 1;
                y = y;
                t++;
            }
        }
    }
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
}