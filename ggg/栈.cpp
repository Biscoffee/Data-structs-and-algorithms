#include <stdio.h>
#include <stdbool.h>

#define MAXSIZE 100 // 定义栈的最大大小

typedef struct {
    int data[MAXSIZE];
    int top;
} stack;

void init(stack *s) {
    s->top = -1;
}

// 判断栈是否为空
bool isEmpty(stack *s) {
    return s->top == -1;
}

// 判断栈是否满
bool isFull(stack *s) {
    return s->top == MAXSIZE - 1;
}

// 入栈
void push(stack* s, int x) {
    if (isFull(s)) {
        printf("栈满\n");
        return;
    }
    s->data[++s->top] = x;
}

// 出栈
bool pop(stack *s, int *x) {
    if (isEmpty(s)) {
        printf("栈为空\n");
        return false;
    }
    *x = s->data[s->top--]; // 先取值，再减少 top
    return true;
}

// 打印栈
void printStack(stack *s) {
    if (isEmpty(s)) {
        printf("栈为空\n");
        return;
    }
    printf("栈内容: ");
    for (int i = 0; i <= s->top; i++) {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}

int main() {
    stack s;
    init(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    printStack(&s);

    int val;
    if (pop(&s, &val)) {
        printf("出栈: %d\n", val);
    }
    printStack(&s);

    return 0;
}