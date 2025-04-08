#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10001
int main()
{
    int n, i, j,count=0;
    int a[MAX][4], s[MAX] = {0};
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
            scanf("%d%d%d", &a[i][1],&a[i][2],&a[i][3]);
            s[i] = a[i][1]+a[i][2]+a[i][3];
        
    }
    for (i = 1; i <= n; i++)
    {
        for (j = i+1; j <= n; j++)
        {
            if(abs(a[i][1]-a[j][1])<=5&&
            abs(a[i][2]-a[j][2])<=5&&
            abs(a[i][3]-a[j][3])<=5&&
            abs(s[i]-s[j])<=10)count++;    
                       
        }
    }
    printf("%d",count);