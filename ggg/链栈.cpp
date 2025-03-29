#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 链栈结点
typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode;

// 链栈结构
typedef struct {
    StackNode *top;
    int count;
} LinkStack;

// 初始化链栈
void InitStack(LinkStack *stack) {
    stack->top = NULL;
    stack->count = 0;
}

// 入栈操作
void push(LinkStack *s, int x) {
    StackNode *p = (StackNode *)malloc(sizeof(StackNode));
    if (p == NULL) { // 确保内存分配成功
        printf("内存分配失败！\n");
        return;
    }
    p->data = x;
    p->next = s->top;
    s->top = p;
    s->count++;
    printf("入栈: %d\n", x);
}

// 出栈操作
bool pop(LinkStack *s, int *x) {
    if (s->top == NULL) {
        printf("栈为空，无法出栈！\n");
        return false; // 失败返回 false
    }
    StackNode *p = s->top;
    if (x != NULL) {
        *x = p->data;
    }
    s->top = s->top->next;
    free(p);
    s->count--;
    
    if (x != NULL) {
        printf("出栈: %d\n", *x);
    }
    return true; // 成功返回 true
}

// 打印栈
void printStack(LinkStack *s) {
    StackNode *p = s->top;
    printf("当前栈内容: ");
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 测试代码
int main() {
    LinkStack stack;
    InitStack(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    printStack(&stack);

    int val;
    if (pop(&stack, &val)) {
        printf("成功出栈: %d\n", val);
    }
    printStack(&stack);

    return 0;
}