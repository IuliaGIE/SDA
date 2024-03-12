#include <stdio.h>
#include <stdlib.h>
typedef struct node {
void * data;
struct node * next;
struct node * prev;
} node;
typedef struct TDoubleLinkedList {
    node *sentinel;
    int len;
} TDoubleLinkedList;
void init(TDoubleLinkedList *list) {
    list->sentinel = (node*)malloc(sizeof(node));
    list->sentinel->next = list->sentinel;
    list->sentinel->prev = list->sentinel;
    list->len = 0;
}
int addNode(TDoubleLinkedList *list, void *data) {
    if (list == NULL) {
        return -1;
    }
    node *new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        return -1;
    }
    new_node->data = data;
    new_node->prev = list->sentinel->prev;
    new_node->next = list->sentinel;
    list->sentinel->prev->next = new_node;
    list->sentinel->prev = new_node;
    list->len++;
    return list->len - 1;
}
void freeList(TDoubleLinkedList *list) {
    if (list == NULL) {
        return;
    }
    node *temp = list->sentinel->next;
    while (temp != list->sentinel) {
        node *current = temp;
        temp = temp->next;
        free(current->data);
        free(current);
    }
    free(list->sentinel);
    list->sentinel = NULL;
    list->len = 0;
}
void printList(TDoubleLinkedList *list) {
    if (list == NULL) {
        return;
    }
    node *temp = list->sentinel->next;
    while (temp != list->sentinel) {
        printf("%d ", *(int*)temp->data);
        temp = temp->next;
    }
    printf("\n");
}
void removeNode(TDoubleLinkedList *list, int index) {
    if (list == NULL || index < 0 || index >= list->len) {
        return;
    }
    node *temp = list->sentinel->next;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    free(temp->data);
    free(temp);
    list->len--;
}

int main(){
    TDoubleLinkedList *list;
    init(&list);

    int a = 1, b = 2, c = 3, d = 4;
    addNode(list, &a);
    addNode(list, &b);
    addNode(list, &c);
    addNode(list, &d);
    printList(list);
    removeNode(list, 2);
    printList(list);
    freeList(list);
    printList(list);
    return 0;
}