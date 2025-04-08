#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1001
int main()
{
    int s, s1, s2, s3, a[MAX] = {0},max=0;
    scanf("%d%d%d", &s1, &s2, &s3);
    int i, j, k;
    for (i = 1; i <= s1; i++)
    {
        for (j = 1; j <= s2; j++)
        {
            for (k = 1; k <= s3; k++)
            {
                s = i + j + k;
                a[s]++;
                if(s>max)max=s;
 
            }
        }
    }
    int t = 0, m;
    for (i = 1; i <= max; i++)
    {
        if (a[i] > t)
        {
            t = a[i];
            m = i;
        }
    }
    printf("%d", m);
}
