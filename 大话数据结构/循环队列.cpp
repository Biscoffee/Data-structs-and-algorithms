#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5 // 定义队列最大容量

typedef struct {
    int data[MAX_SIZE]; // 队列存储数组
    int front; // 头指针
    int rear;  // 尾指针
} CircularQueue;

// 初始化队列
void InitQueue(CircularQueue* queue) {
    queue->front = 0;
    queue->rear = 0;
}
// 判断队列是否为空
int IsEmpty(CircularQueue* queue) {
    return queue->front == queue->rear;
}
// 判断队列是否已满
int IsFull(CircularQueue* queue) {
    return (queue->rear + 1) % MAX_SIZE == queue->front;
}

// 入队操作
int Enqueue(CircularQueue* queue, int value) {
    if (IsFull(queue)) {
        printf("队列已满，无法入队！\n");
        return 0;
    }

    queue->data[queue->rear] = value; // 在 rear 位置插入元素
    queue->rear = (queue->rear + 1) % MAX_SIZE; // rear 循环前进
    printf("入队：%d\n", value);
    return 1;
}

// 出队操作
int Dequeue(CircularQueue* queue, int* value) {
    if (IsEmpty(queue)) {
        printf("队列为空，无法出队！\n");
        return 0;
    }

    *value = queue->data[queue->front]; // 取出 front 位置的元素
    queue->front = (queue->front + 1) % MAX_SIZE; // front 循环前进
    printf("出队：%d\n", *value);
    return 1;
}

// 遍历队列
void PrintQueue(CircularQueue* queue) {
    if (IsEmpty(queue)) {
        printf("队列为空！\n");
        return;
    }

    printf("队列元素：");
    int i = queue->front;
    while (i != queue->rear) {
        printf("%d ", queue->data[i]);
        i = (i + 1) % MAX_SIZE;
    }
    printf("\n");
}