#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    void* data;
    struct node* next;
} node;
typedef struct TList {
    node* head;
    int len;
} TList;
void initL(TList **list) {
    *list = (TList*)malloc(sizeof(node));
    (*list)->head = NULL;
    (*list)->len = 0;
}
int length_list(TList *list) {
    return list->len;
}
int add_node(TList *list, int n, void* data){
    if (n < 0 || n > list->len) {
        return -1;
    }
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    if (n == 0) {
        new_node->next = list->head;
        list->head = new_node;
    } 
        else{
            node* current = list->head;
        for (int i = 0; i < n - 1; i++) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
        }
    list->len++;
    return 1;
}
void* Remove_nod(TList *list, int n){
    int i;
    if(n < 0 || n >= list->len)
        return NULL;
    node* temp = list->head;
    void* elib;
    if(n == 0){
        list->head = temp->next;
        elib = temp->data;
        free(temp);
        list->len--;
        return elib;   
}
    for(i = 0; i < n - 1; i++)
        temp = temp->next;
    node* deleted = temp->next;
    temp->next = deleted->next;
    elib = deleted->data;
    free(deleted);
    list->len--;
    return elib;
}
void print_int_list(TList *list) {
    node* temp = list->head;
    while (temp != NULL) {
        printf("%d ", *(int*)temp->data);
        temp = temp->next;
    }
    printf("\n");
}
void print_string_list(TList *list) {
    node *current = list->head;
    while (current != NULL) {
        printf("%p ", current->data);
        current = current->next;
    }
    printf("\n");
}
void free_list(TList **list) {
    node *current = (*list)->head;
    while (current != NULL) {
        node *temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
    free(*list);
    *list = NULL;
}
int main(){
    TList* list;
    initL(&list);

    int a = 1, b = 2, c = 3;
    add_node(list, 0, &a);
    add_node(list, 1, &c);
    add_node(list, 1, &b);
    print_int_list(list);
    print_string_list(list);
    Remove_nod(list, 1);
    print_int_list(list);
    Remove_nod(list, 0);
    print_int_list(list);
    Remove_nod(list, 0);
    print_int_list(list);
    return 0;
}