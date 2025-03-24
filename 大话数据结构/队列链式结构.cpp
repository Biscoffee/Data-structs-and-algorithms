#include <stdio.h>
#include <stdlib.h>

// 定义链式队列节点
typedef struct Node {
    int data;           // 数据域
    struct Node* next;  // 指向下一个节点
} Node;

// 定义链式队列结构
typedef struct {
    Node* front;  // 头指针，指向队列头部
    Node* rear;   // 尾指针，指向队列尾部
} LinkedQueue;

// 初始化链式队列
void InitQueue(LinkedQueue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

// 判断队列是否为空
int IsEmpty(LinkedQueue* queue) {
    return queue->front == NULL;
}

// 入队操作
void Enqueue(LinkedQueue* queue, int value) {
    // 创建新节点
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (IsEmpty(queue)) {
        // 如果队列为空，新节点既是队头也是队尾
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        // 如果队列不为空，将新节点插入到队尾
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    printf("入队：%d\n", value);
}

// 出队操作
int Dequeue(LinkedQueue* queue, int* value) {
    if (IsEmpty(queue)) {
        printf("队列为空，无法出队！\n");
        return 0;
    }

    Node* temp = queue->front; // 记录队头节点
    *value = temp->data;       // 取出数据
    queue->front = queue->front->next; // 让 front 指向下一个节点

    if (queue->front == NULL) {
        queue->rear = NULL; // 如果队列为空，rear 也置为空
    }

    free(temp); // 释放旧的头节点
    printf("出队：%d\n", *value);
    return 1;
}