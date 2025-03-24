typedef struct DulNode {
    int data;
    struct DulNode *prior, *next;
} DulNode, *DuLinkList;

// 插入   在ai(p)和ai+1(p->next)之间插入元素s

s ->prior = p;
s -> next = p -> next;
p -> next -> prior = s;
p -> next = s;

// 删除  删除节点p
p -> prior -> next = p -> next;
p -> next -> prior = p -> prior;
free(p);
