#include <stdio.h>
#include "Queue.h"

int main() {
    Queue* q = createQueue();
    printf("Coada este goala? %d\n", isQueueEmpty(q));
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    printf("Coada este goala? %d\n", isQueueEmpty(q)); 
    printf("Primul element: %d\n", front(q)); 
    dequeue(q);
    printf("Primul element: %d\n", front(q)); 
    dequeue(q);
    printf("Primul element: %d\n", front(q)); 
    dequeue(q);
    printf("Coada este goala? %d\n", isQueueEmpty(q));
    destroyQueue(q);
    return 0;
}
