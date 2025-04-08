#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100001
int main()
{
    int l,m,s;
    int i,j;
    int a[2],b[MAX];
    int sum=0;
    scanf("%d%d",&l,&m);
    for(i=0;i<=l;i++){
        b[i]=0;
    }
    for(i=1;i<=m;i++){
        for(j=0;j<2;j++)
            scanf("%d",&a[j]);
            for(j=0;j<=l;j++)
                if(j>=a[0]&&j<=a[1])b[j]=1;
            
        
    }
    for(i=0;i<=l;i++){
        if(b[i]==0)sum++;
    }
    printf("%d",sum);
 
}
