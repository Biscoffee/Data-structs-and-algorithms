//栈的结构定义
typedef struct {
    int data[MAXSIZE];
    int top;  //用于栈顶指针
}SqStack;

//初始化栈
void InitStack(SqStack *S){
    S->top = -1;
}

//进栈操作
status Push(SqStack *S,int x){
    if(S -> top == MAXSIZE -1){
        return ERROR;
    }
    S -> top++;
    S -> data[S->top] = x;
    return OK;
}

//出栈操作
status Pop(SqStack *S,int *x){
    if(S -> top == -1){
        return ERROR;
    }
    *x = S -> data[S->top];
    S -> top--;
    return OK;
}