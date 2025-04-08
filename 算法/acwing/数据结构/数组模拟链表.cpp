//head表示头节点下标
//e[i]表示节点i的值
//ne[i]表示节点i的next指针是多少
//idx表示当前用到了哪个节点
#include <iostream>
using namespace std;

int head,e[N],ne[N],idx;

void init()
{
    head = -1;
    idx = 0;
}

void add_to_head(int x)
{
     e[idx] = x;
     ne[idx] = head;
     head = idx;
     idx++;
}

void add(int k,int x)  //在第k个插入一个数x
{
    e[idx] = x;
    ne[idx] = ne[k];
    ne[k] = idx;
    idx++;
}

void remove(int k) //删除第k个点后面的点
{
    ne[k] = ne[ne[k]];
}

 