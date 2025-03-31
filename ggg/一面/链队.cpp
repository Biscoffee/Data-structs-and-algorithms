typedef struct Node{
    int data;
    struct Node *next;
}Node;
typedef struct {
    Node *front;
    Node *rear;
}

bool isEmpty(Queue *q) {
    if (q->front == NULL && q->rear == NULL) {
        printf("队列为空\n");
        return true;
    } else {
        printf("队列不为空\n");
        return false;
    }
}   
void enqueue(Queue *q, int x) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存分配失败！\n");
        return;
    }
    newNode->data = x;
    newNode->next = NULL;
    if(q->rear == NULL){
        q->front = newNode;
        q->rear = newNode;
    } else{
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

void dequeue(Queue *q, int *x) {
    if (q->front == NULL) {
        printf("队列为空，无法出队！\n");
        return;
    }
    Node *p = q->front;
    *x = p->data;
    q->front = p->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(p);
}