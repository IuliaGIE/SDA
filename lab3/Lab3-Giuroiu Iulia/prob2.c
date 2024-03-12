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
int find_middle_position(TList *list) {
    node *s = list->head;
    node *f = list->head;
    int ct = 0;
    while (f != NULL && f->next != NULL) {
        s = s->next;
        f = f->next->next;
        ct++;
    }
    if(f == NULL)
        return ct;
    else 
        return ct  + 1;
}

int main(){
    TList* list;
    initL(&list);
    int a = 1, b = 2, c = 3, d = 4, e = 5;
    add_node(list, 0, &a);
    add_node(list, 1, &c);
    add_node(list, 1, &b);
    add_node(list, 2, &d);
    add_node(list, 2, &e);
    int middle_l = find_middle_position(list);
    printf("%d\n", middle_l);
}