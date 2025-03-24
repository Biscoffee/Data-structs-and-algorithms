// 当两个指针相差1时，即top1 + 1 == top2时，栈满

typedef struct {
    int data[MAXSIZE];
    int top1;
    int top2;
} SqDoubleStack;

//插入元素  除了要插入的元素值参数外，还需一个栈号参数，以区分是栈1还是栈2
int Push(SqDoubleStack *S, int element, int stackNumber) {
    if (S->top1 + 1 == S->top2) {
        return ERROR;
    }
    if (stackNumber == 1) {
        S->data[++S->top1] = element;
    } else if (stackNumber == 2) {
        S->data[--S->top2] = element;
    }
    return OK;
}

//删除元素  除了要删除的元素值参数外，还需一个栈号参数，以区分是栈1还是栈2
int Pop(SqDoubleStack *S, int *element, int stackNumber) {
    if (stackNumber == 1) {
        if (S->top1 == -1) {
            return ERROR;
        }
        *element = S->data[S->top1--];
    } else if (stackNumber == 2) {
        if (S->top2 == MAXSIZE) {
            return ERROR;
        }
        *element = S->data[S->top2++];
    }
    return OK;
}