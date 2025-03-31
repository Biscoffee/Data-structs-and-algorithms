#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10001
int main()
{
    int n,m,s=0,t,a[MAX]={0};
    scanf("%d",&n);
    int i,j;
    for(i=1;s!=n*n;i++){
        scanf("%d",&m);
        if(i%2==0){
        for(j=s+1;j<=s+m;j++)a[j]=1;
        }
        s+=m;
 
    }
    for(i=1;i<=n*n;i++){
        printf("%d",a[i]);
        if(i%n==0)printf("\n");
    }
  
}
