#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 101
int main()
{
    int n,a[MAX][MAX]={0};
    scanf("%d",&n);
    int i,j;
    for(i=1;i<=n;i++){
        a[i][1]=a[i][i]=1;
    }
    for(i=1;i<=n;i++){
        for(j=2;j<=i-1;j++){
            a[i][j]=a[i-1][j]+a[i-1][j-1];
        }
    }
    for(i=1;i<=n;i++){
        for(j=1;j<=i;j++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
}