#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 101
int main()
{
    int n,m,k,i,j,t,x,y,x2,y2;
    int a[MAX][MAX]={0};
    scanf("%d%d%d",&n,&m,&k);
    for(i=2;i<=m+1;i++){
        scanf("%d%d",&x,&y);
        a[x][y]=2;
        a[x-1][y]=a[x-2][y]=a[x+1][y]=a[x+2][y]=a[x][y-1]=a[x][y-2]=a[x][y+1]=a[x][y+2]=a[x-1][y-1]=a[x-1][y+1]=a[x+1][y-1]=a[x+1][y+1]=1;
    }
    for(i=m+2;i<=m+k+1;i++){
        scanf("%d%d",&x2,&y2);
        a[x2][y2]=3;
        for(j=x2-2;j<=x2+2;j++){
            for(t=y2-2;t<=y2+2;t++){
                if(a[j][t]==0)a[j][t]=1;
            }
        }
    }
    int count=0;
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(a[i][j]==0)count++;
            //printf("%d",a[i][j]);
        }
        //printf("\n");
    }
    printf("%d",count);
}
