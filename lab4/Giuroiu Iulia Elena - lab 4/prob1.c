#include <stdio.h>
#include <stdlib.h>
typedef struct node {
void * data;
struct node * next;
struct node * prev;
} node;
typedef struct TDoubleLinkedList {
node *head;
node *tail;
int len;
} TDoubleLinkedList;
void init(TDoubleLinkedList **list) {
    *list = (TDoubleLinkedList *) malloc(sizeof(TDoubleLinkedList));
    (*list)->head = NULL;
    (*list)->tail = NULL;
    (*list)->len = 0;
}
void add(TDoubleLinkedList *list, void * data, int n) {
    if (n < 0 || n > list->len) {
        printf("Pozitie in afara listei");
        return;
    }
    node *nnode = (node *)malloc(sizeof(node));
    nnode->data = data;
    if (n == 0) {
        nnode->next = list->head;
        nnode->prev = NULL;
        if(list->head != NULL)
            list->head->prev = nnode;
        else
            list->tail = nnode;
        list->head = nnode;
    }
    else if (n == list->len) {
        nnode->next = NULL;
        nnode->prev = list->tail;
        if(list->tail != NULL)
            list->tail->next = nnode;
        else
            list->head = nnode;
        list->tail = nnode;
        }
    else{
        node *temp;
        int i;
    if(n < list->len/2){
        temp = list->head;
        for(i = 0; i < n; i++)
            temp = temp->next;
    }
    else{
        for(i = list->len-1; i > n; i--)
            temp = temp->prev;
    }
    nnode->next = temp;
    nnode->prev = temp->prev;
    temp->prev->next = nnode;
    temp->prev = nnode;
    }
    list->len++;
    
}
void printList(TDoubleLinkedList *list) {
    if (list == NULL || list->len == 0) {
        printf("Lista este goala.\n");
        return;
    }
    printf("Lista dublu inlantuita contine %d elemente:\n", list->len);
    node *temp = list->head;
    while (temp != NULL) {
        printf("%d -> ", *(int*)temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
void printListReverse(TDoubleLinkedList *list) {
    if (list == NULL || list->len == 0) {
    printf("Lista este goala.\n");
    return;
    }
    printf("Lista dublu inlantuita inversata contine %d elemente:\n", list->len);
    node *temp = list->tail;
    while (temp != NULL) {
        printf("%d -> ", *(int*)temp->data);
        temp = temp->prev;
    }
    printf("NULL\n");
}
void Remove(TDoubleLinkedList *list, void * data, int n) {
    if (list == NULL || list->len <= n) {
        return;
    }
    
    node *current = list->head;
    int i;
    
    for (i = 0; i < n; i++) {
        current = current->next;
    }
    
    if (current == list->head) {
        list->head = current->next;
    }
    if (current == list->tail) {
        list->tail = current->prev;
    }
    
    current->prev->next = current->next;
    current->next->prev = current->prev;
    
    free(current);
    list->len--;
}
void freeList(TDoubleLinkedList **list) {
    if (*list == NULL) {
        return;
    }
    node *temp = (*list)->head;
    while (temp != NULL) {
        node *current = temp;
        temp = temp->next;
        if (current->data != NULL) {
            free(current->data);
        }
        current->prev = NULL;
        free(current);
    }
    (*list)->head = NULL;
    (*list)->tail = NULL;
    (*list)->len = 0;
    free(*list);
    *list = NULL;
}

int main(){
    TDoubleLinkedList *list;
    init(&list);

    int a = 1, b = 2, c = 3, d = 4;

    add(list, &a, 0);
    add(list, &b, 1);
    add(list, &c, 2);
    add(list, &d, 3);

    printf("Lista dupa adaugarea elementelor: \n");
    printList(list);
    printListReverse(list);

    Remove(list, &c, 2);

    printf("Lista dupa stergerea elementului: \n");
    printList(list);
    printListReverse(list);
    return 0;
}