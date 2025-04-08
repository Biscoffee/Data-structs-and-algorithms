#include <stdio.h>
#include <math.h>
#include <string.h>
int main(void)
{
	int i,n,count=0;
	char str[40000],temp[200];
	int a[40000],len;
	
	while((scanf("%s",temp))!=EOF)
		strcat(str,temp);
	len=strlen(str);
	n=(int)sqrt(len);
	
	for(i=0;i<=len;i++)
		a[i]=str[i]-'0';
	
	if(a[0]==1)
	{
		printf("%d 0 ",n);
		i++;
	}
	else
		printf("%d ",n);
		
	for(i=0;i<len-1;i++)
	{
		if(a[i]==a[i+1])
			count++;
		else
		{
			printf("%d ",++count);
			count=0;
		}
	}
	if(a[len-2]==a[len-1])
		printf("%d",++count);
	else
		printf("1");
	return 0;
}

