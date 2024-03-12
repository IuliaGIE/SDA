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
int add_in_order(TDoubleLinkedList *list, void *data) {
    if (list == NULL) {
        return -1;
    }
    node *new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        return -1;
    }
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    int pos = 0;
    node *current = list->head;
    while (current != NULL && *(int*)current->data < *(int*)data) {
        current = current->next;
        pos++;
    }
    if (current == NULL) {
        new_node->prev = list->tail;
        if (list->tail != NULL) {
            list->tail->next = new_node;
        }
        list->tail = new_node;
        if (list->head == NULL) {
            list->head = new_node;
        }
    } else if (current->prev == NULL) {
        new_node->next = current;
        current->prev = new_node;
        list->head = new_node;
    } else {
        new_node->prev = current->prev;
        current->prev->next = new_node;
        new_node->next = current;
        current->prev = new_node;
    }
    list->len++;
    return pos;
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

int main(){
    TDoubleLinkedList *list;
    init(&list);

    int a = 1, b = 2, c = 3, d = 4;
    add(list, &a, 0);
    add(list, &b, 1);
    add(list, &c, 2);
    printList(list);
    add_in_order(list, &d);
    //add(list, &d, 3);

    
    printList(list);
    return 0;
}