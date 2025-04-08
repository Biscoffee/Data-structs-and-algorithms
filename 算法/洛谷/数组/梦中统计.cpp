#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    int m,n;
    scanf("%d%d",&m,&n);
    int i,j,k,t;
    int a[10]={0};
    for(i=m;i<=n;i++)
    {
        k=i;
        while(k!=0){
            t=k%10;
            a[t]++;
            k=k/10;
        }
    }
    for(i=0;i<=9;i++){
        printf("%d ",a[i]);
    }
    return 0;
}