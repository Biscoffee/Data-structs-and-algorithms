typedef struct {
    int data[MAXSIZE];
    int front;  // 头指针
    int rear;   // 指向队尾元素的下一个位置
} Queue;  // front= rear 队列为空

void init(Queue *q) {
    q->front = q->rear = 0;
}
bool isEmpty(Queue *q) {
    if (q->front == q->rear) {
        return true;
    }
    return false;
}
void enqueue(Queue *q, int x) {
    if ((q->rear + 1) % MAXSIZE == q->front) {
        printf("队列已满\n");
        return;
    }
    q->data[q-> rear] = x;
    q->rear = (q->rear + 1) % MAXSIZE;
}

void dequeue(Queue *q, int *x) {
    if (q->front == q->rear) {
        printf("队列为空\n");
        return;
    }
    *x = q->data[q->front];
    q->front = (q->front + 1) % MAXSIZE;
}