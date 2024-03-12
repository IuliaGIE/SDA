#include <stdlib.h>

typedef struct QueueNode {
    int elem;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
    long size;
} Queue;

// function to create a new queue
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

// function to check if a queue is empty
int isQueueEmpty(Queue* q) {
    return q->front == NULL;
}

// function to add an element to the queue
void enqueue(Queue* q, int elem) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->elem = elem;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}

// function to get the value of the first element in the queue
int front(Queue* q) {
    return q->front->elem;
}

// function to remove an element from the queue
void dequeue(Queue* q) {
    if (q->front == NULL) {
        return;
    }
    QueueNode* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    q->size--;
}

// function to destroy a queue
void destroyQueue(Queue* q) {
    while (q->front != NULL) {
        dequeue(q);
    }
    free(q);
}
