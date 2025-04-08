#include<stdio.h>
 
int main(){
	int w,x,h,q,x1,y1,z1,x2,y2,z2;
	int que[30][30][30];
	scanf("%d%d%d",&w,&x,&h);
	scanf("%d",&q);
	int sum=w*x*h;
	for(int i=1;i<=w;i++)
		{
			for(int j=1;j<=x;j++)
			{
				for(int k=1;k<=h;k++)
				{
					que[i][j][k]=1;
				}
			}
		}
	while(q!=0)
	{
		scanf("%d%d%d%d%d%d",&x1,&y1,&z1,&x2,&y2,&z2);
		for(int i=x1;i<=x2;i++)
		{
			for(int j=y1;j<=y2;j++)
			{
				for(int k=z1;k<=z2;k++)
				{
					if(que[i][j][k]==1)
					{
						sum--;
						que[i][j][k]=0;
					}
				}
			}
		}
		q--;
	}
	printf("%d",sum);
	return 0;
}