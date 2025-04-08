#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100001
int main()
{
    int n,i=1,j,count=0;
    scanf("%d",&n);
    int a[MAX];
    while(n!=1){
        a[i]=n;
        if(n%2==0)n=n/2;
        else n=n*3+1;
        i++;
        count++;
    }
    a[count+1]=1;
    for(j=count+1;j>=1;j--){
        printf("%d ",a[j]);
    }
 
}