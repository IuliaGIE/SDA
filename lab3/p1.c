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
void* Remove(TList *list, int n) {
    if (n < 0 || n >= list->len || list->len == 0) {
        return NULL; // n este in afara intervalului valid sau lista este vida
    }
    node* current = list->head;
    if (n == 0) { // daca stergem primul element
        list->head = current->next;
        void* data = current->data;
        free(current);
        list->len--;
        return data;
    }
    for (int i = 0; i < n-1; i++) {
        current = current->next; // parcurgem lista pana la pozitia n-1
    }
    node* to_remove = current->next; // retinem nodul de pe pozitia n
    current->next = to_remove->next; // legam nodul precedent de nodul urmator
    void* data = to_remove->data;
    free(to_remove);
    list->len--;
    return data;
}

void print_list(TList *list) {
    node* curr = list->head;
    while (curr != NULL) {
        printf("%d ", *(int*)curr->data);
        curr = curr->next;
    }
    printf("\n");
}
int main(){
    TList* list;
    initL(&list);

    int a = 1, b = 2, c = 3;
    add_node(list, 0, &a);
    add_node(list, 1, &c);
    add_node(list, 1, &b);
    print_list(list);

    Remove(list, 1);
    print_list(list);

    Remove(list, 0);
    print_list(list);

   // Remove(list, 1);
    print_list(list);

    return 0;
}