#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char data;
    struct node *next;
    struct node *prev;
} node;

typedef struct TDoubleLinkedList
{
    node *sentinel;
    node *tail;
    node *finger; // pozitia curenta in lista
    int len;
} TDoubleLinkedList;

typedef struct StackNode{
    node before;
    struct StackNode *next;
}StackNode;

typedef struct Stack{
    StackNode* head;
    long size;
}Stack;

void initStack(Stack *s) {
    s->head = NULL;
    s->size = 0;
}

void push(Stack *s, char data) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    newNode->before.data = data;
    newNode->next = s->head;
    s->head = newNode;
    s->size++;
}

char pop(Stack *s) {
    if (s->head == NULL) {
        printf("Stack is empty\n");
        return '\0';
    }
    char data = s->head->before.data;
    StackNode *temp = s->head;
    s->head = s->head->next;
    free(temp);
    s->size--;
    return data;
}

void printStack(Stack *s) {
    printf("Stack size: %ld\n", s->size);
    StackNode *temp = s->head;
    while (temp != NULL) {
        printf("%c ", temp->before.data);
        temp = temp->next;
    }
    printf("\n");
}

void freeStack(Stack *s) {
    StackNode *temp;
    while (s->head != NULL) {
        temp = s->head;
        s->head = s->head->next;
        free(temp);
    }
    s->size = 0;
}

int main() {
    Stack s;
    initStack(&s);
    push(&s, 'a');
    push(&s, 'b');
    push(&s, 'c');
    push(&s, 'd');
    push(&s, 'e');
    printStack(&s);
    char popped = pop(&s);
    printf("Popped: %c\n", popped);
    printStack(&s);
    freeStack(&s);
    return 0;
}
