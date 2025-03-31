#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10001
int main(){
    int t,n,m,count=0;
    int i,j,k;
    int a[7]={0},b[34]={0};
 
    scanf("%d",&n);
    for(i=1;i<=7;i++){
        scanf("%d",&t);
        b[t]=1;
    }
    for(i=1;i<=n;i++){
        count=0;
        for(j=1;j<=7;j++){
            scanf("%d",&m);
          if(b[m]==1)count++;
        }
        a[7-count]++;
    }
 
    for(i=0;i<=6;i++){
        printf("%d ",a[i]);
 
    }
}
