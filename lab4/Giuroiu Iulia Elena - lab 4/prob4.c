#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void removeDuplicates(TDoubleLinkedList *list) {
    if (list == NULL || list->head == NULL) {
        return;
    }
    
    node *current = list->head;
    node *prev = NULL;
    int hashTable[1000] = {0}; // marimea tabelei hash depinde de numarul maxim de elemente din lista
    
    while (current != NULL) {
        int val = *(int *)(current->data); // consideram ca elementele listei sunt de tip int
        if (hashTable[val] == 1) { // daca valoarea a fost deja gasita in lista, eliminam elementul curent
            prev->next = current->next;
            if (current->next != NULL) {
                current->next->prev = prev;
            }
            node *temp = current;
            current = current->next;
            free(temp->data);
            free(temp);
            list->len--;
        } else { // altfel, adaugam valoarea in tabela hash
            hashTable[val] = 1;
            prev = current;
            current = current->next;
        }
    }
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
    int arr[] = {1, 2, 3, 4, 1, 5, 2};
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
        int *val = malloc(sizeof(int));
        *val = arr[i];
        add(list, val, i);
    }
    printf("Lista initiala: ");
    printList(list);
    
    removeDuplicates(list);
    printf("Lista fara duplicate: ");
    printList(list);
    
    return 0;
}