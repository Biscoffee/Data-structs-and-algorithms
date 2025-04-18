#include<iostream>
#include<cstring>
using namespace std;

const int N  = 100010;
int n,m;
int p[N];

int find(int x)   //返回x的祖宗节点 + 路经压缩
{
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];

}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++)  p[i] = i;
    while(m --)
    {
        char op[2];
        int a,b;
        scanf("%s%d%d",op,&a,&b);
        if("op[0] == 'I")  p[find(a)] = find(b);
        else{
            if(find(a) == find(b)) puts("Yes");
            else puts("No");
        } 
    }
}