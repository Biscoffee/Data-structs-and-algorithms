//通常对于链栈来说，是不需要头结点的，头结点往往是为了操作的方便而设立的，但是对于链栈来说，
// 第⼀个节点就是栈顶，⽽最后⼀个节点就是栈底，⽽栈底⽆法再进栈了，因此就不需要头结点了，
// 否则会浪费⼀块存储区域。

typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode;

typedef struct{
    StackNode *top;
} LinkStack;

//初始化
status InitStack(LinkStack *stack) {
    stack->top = NULL;
}

// 判断栈是否为空
int IsEmpty(LinkedStack* stack) {
    return stack->top == NULL;
}
//StackNode 是链栈的 基本单元 ，每个节点存储一个元素，并通过 next 指针与其他节点连接，形成链表。 
//LinkStack 是链栈的 管理结构 ，通过 top 指针指向链表的头节点（即栈顶节点），并通过 count 记录栈中元素的数量。
// LinkStack
// +-------+       +-------+       +-------+       +-------+
// | top   | ----> | data  |       | data  |       | data  |
// | count |       | next  | ----> | next  | ----> | next  | ----> NULL
// +-------+       +-------+       +-------+       +-------+
//                 StackNode       StackNode       StackNode

// 入栈操作
void Push(LinkedStack* stack, int value) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode)); // 分配新结点
    newNode->data = value;     // 赋值
    newNode->next = stack->top; // 新结点指向当前栈顶
    stack->top = newNode;      // 更新栈顶指针
    printf("入栈：%d\n", value);
}

// 出栈操作
int Pop(LinkedStack* stack) {
    if (IsEmpty(stack)) {
        printf("栈为空，无法出栈！\n");
        return -1; // 返回错误标志
    }
    
    StackNode* temp = stack->top; // 记录栈顶结点
    int value = temp->data;       // 获取数据
    stack->top = temp->next;      // 更新栈顶指针
    free(temp);                   // 释放栈顶结点
    printf("出栈：%d\n", value);
    
    return value;
}

