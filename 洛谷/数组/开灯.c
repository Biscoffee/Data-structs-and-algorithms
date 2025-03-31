#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000001
int main()
{
    long int n;
    int light[MAX] = {0};
    scanf("%d", &n);
    double a;
    int i,j, t, s, max = 0;
    for (i = 1; i <= n; i++)
    {
        scanf("%lf %d", &a, &t);
        //printf("%f %d\n",a,t);
        for (j =1; j <=t; j++)
        {
            s = 1.0 * j * a;
            //printf("s=%d\n",s);
            if (light[s] == 0)
                light[s] = 1;
            else
                light[s] = 0;
        }
        if (a * t > max)
            max = a * t;
            //printf("max=%d\n",max);
    }
 
    for (i = 1; i <= max; i++)
    {
        if (light[i] == 1)
        {
            printf("%d", i);
            break;
        }
    }
}