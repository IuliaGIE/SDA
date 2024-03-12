// Giuroiu Iulia Elena - 313CC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100
// coada de comenzi
typedef struct {
   char **items;
   int front;
   int rear;
   int size;
} Queue;

// banda magica
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

// stivele UNDE/REDO
typedef struct StackNode{
    node *index;
    struct StackNode *next;
}StackNode;

typedef struct Stack{
    StackNode* head;
    long size;
}Stack;

// functia de init pt banda
void init(TDoubleLinkedList *list)
{
    list->sentinel = (node *)malloc(sizeof(node));
    list->finger = (node *)malloc(sizeof(node));
    list->sentinel->data = '\0';
    list->sentinel->prev = NULL;
    list->tail = (node *)malloc(sizeof(node));
    list->tail->data = '\0';
    list->sentinel->next = list->tail;
    //list->sentinel->next->data = (char *)malloc(2);
    list->sentinel->next->data = '#';
    list->finger = list->tail;
    list->len = 0;
}

// eliberarea bandei
void freeList(TDoubleLinkedList *list)
{
    node *current = list->sentinel;
    node *temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        list->sentinel->next = current;
        free(temp);
    }
    list = NULL;
}

// alocarea de memorie pt coada
void initQueue(Queue *q, int size) {
   q->items = (char **)malloc(size * sizeof(char *));
   q->size = size;
   q->front = 0;
   q->rear = -1;
}

// functia de init stiva
void initStack(Stack *s) {
    s->head = (StackNode*) malloc(sizeof(StackNode));
    s->head->index = NULL;
    s->head->next = NULL; 
    s->size = 0;
}

// adaugarea in stiva
void push(Stack *s, node *index){
    StackNode *newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->index = index;
    newNode->next = s->head;
    s->head = newNode;
    s->size++;
}

//scoaterea din stiva
node* pop(Stack *s){
    if (s->head == NULL) {
        return NULL;
    }
    StackNode *topNode = s->head;
    node *index = topNode->index;
    s->head = topNode->next;
    free(topNode);
    s->size--;
    return index;
}

// golirea stivei
void clearStack(Stack* stack) {
    while (stack->head != NULL) {
        StackNode* temp = stack->head;
        stack->head = stack->head->next;
        free(temp);
    }
    stack->size = 0;
}

// afisarea elementelor din banda
void SHOW(FILE *fpOut, TDoubleLinkedList *list) {
    node *current = list->sentinel->next;
    while (current != NULL) {
        if(current == list->finger)
            fprintf(fpOut, "|%c|", current->data);
        else
            fprintf(fpOut, "%c", current->data);
        current = current->next;
    }
    fprintf(fpOut, "\n");
}

// afiseaza elementul curent
void SHOW_CURRENT(FILE *fpOut, TDoubleLinkedList *list){
    fprintf(fpOut, "%c\n", list->finger->data);
}

// adaugare element 
void add(TDoubleLinkedList *list, char item){
    node *nnode = (node *)malloc(sizeof(node));
    nnode->data = item;
    nnode->next = NULL;
        nnode->prev = list->finger;
        if(list->finger != NULL)
            list->finger->next = nnode;
        else
            list->tail = nnode;
        list->finger = nnode;
}

// muta la stanga in banda
void MOVE_LEFT(TDoubleLinkedList *list){
    node *current = list->finger;
    if(current != list->sentinel->next)
        list->finger = current->prev;
}

//muta la dreapta in banda
void MOVE_RIGHT(TDoubleLinkedList *list){
    if(list->finger->next != NULL)
        list->finger = list->finger->next;
    else if(list->finger->next == NULL){
        add(list, '#');
    } 
}

void MOVE_RIGHT_CHAR(TDoubleLinkedList *list, char c){
    node *current = list->finger;
    int ok = 0;
    while(current != NULL){
        if(current->data == c){
            ok = 1;
            list->finger = current;
            break;
        }
        current = current->next;
    }
    if(ok == 0)
        add(list, '#');
}

// comanda de UNDO
node* UNDO(TDoubleLinkedList *list, Stack *s){
    node *index = pop(s);
    list->finger = index;
    return index;
}

// comanda de REDO
node* REDO(TDoubleLinkedList *list, Stack *s){
    node *index = pop(s);
    list->finger = index;
    return index;
}

//adauga in coada de comenzi
void enqueue(Queue *q, char *item) {
   q->rear++;
   q->items[q->rear] = (char *)malloc(strlen(item) + 1);
   strcpy(q->items[q->rear], item);
}

// scoate din coada de comenzi
char* dequeue(Queue *q) {
   if (q->rear < q->front) {
      printf("Coada este goala.\n");
      return NULL;
   }
   char *item = q->items[q->front];
   q->front++;
   return item;
}

void freeStack(Stack *s) {
    clearStack(s);
    free(s);
}

int main() {
   FILE *fpIn, *fpOut;
   Queue q;
   Stack sUNDO, sREDO;
   char buffer[MAX_SIZE];
   int n, i;
   fpIn = fopen("tema1.in", "r");
   fpOut = fopen("tema1.out", "w");

   // initializarea listei
   TDoubleLinkedList *list;
   list = (TDoubleLinkedList*)malloc(sizeof(TDoubleLinkedList));
   init(list);

   // Verificare dacă fișierele pot fi deschise
   if (fpIn == NULL || fpOut == NULL) {
      printf("Eroare la deschiderea fișierelor.");
      return -1;
   }

   // Citirea numarului n
   fscanf(fpIn, "%d", &n);

   // Initializarea cozii
   initQueue(&q, n);
   // Initializarea stivelor
   initStack(&sREDO);
   initStack(&sUNDO);
   fgets(buffer, MAX_SIZE, fpIn);
   char c;
   // Citirea urmatoarelor n linii si adaugarea lor in coada
   for (i = 0; i < n; i++) {
      fgets(buffer, MAX_SIZE, fpIn);
      //SHOW(fpOut, list);
      //printf("%d: %s", i, buffer);
      if(strstr(buffer, "EXECUTE") != NULL)
      {
        // scoate prima comanda din coada
        char *item = dequeue(&q);
        //printf("%s", item);
        if(strstr(item, "MOVE_RIGHT_CHAR")!= NULL){
            c = item[16];
            MOVE_RIGHT_CHAR(list, c);
            clearStack(&sUNDO);
            clearStack(&sREDO);
            initStack(&sREDO);
            initStack(&sUNDO);
            //printf("%c\n", c);
            //printf("%s", item);
        }
        else if(strstr(item, "MOVE_LEFT")!= NULL){
            push(&sUNDO, list->finger);
            MOVE_LEFT(list);
            //printf("%s", item);
        }
        else if(strstr(item, "MOVE_RIGHT")!= NULL)
        {
            push(&sUNDO, list->finger);
            MOVE_RIGHT(list);
            //printf("%s", item);
        }
      }
      else if(strstr(buffer, "SHOW_CURRENT") != NULL)
      {
        // afiseaza carcterul curent
        SHOW_CURRENT(fpOut, list);
        clearStack(&sUNDO);
        clearStack(&sREDO);
        initStack(&sREDO);
        initStack(&sUNDO);
        //printf("Afiseaza caracterul curent\n");
      }
      else if(strstr(buffer, "SHOW") != NULL)
      {
        // afiseaza lista
        SHOW(fpOut, list);
        clearStack(&sUNDO);
        clearStack(&sREDO);
        initStack(&sREDO);
        initStack(&sUNDO);
        //printf("Afiseaza lista\n");
      }
      else if(strstr(buffer, "UNDO") != NULL)
      {
        // Face undo
        node *redo = UNDO(list, &sUNDO);
        push(&sREDO, redo);
        //printf("UNDO\n");
      }
      else if(strstr(buffer, "REDO") != NULL)
      {
        // Face redo
        // redo()
        node *undo = REDO(list, &sUNDO);
        push(&sUNDO, undo);
        //printf("REDO\n");
      }
      else enqueue(&q, buffer);
   }

   // Eliberarea memoriei alocate pentru fiecare item din coada
   for (i = q.front; i <= q.rear; i++) {
      free(q.items[i]);
   }

   // eliberam banda
   freeList(list);
   free(list);

   // elibereaza memoria stivelor
    clearStack(&sUNDO);
    freeStack(&sUNDO);
    clearStack(&sREDO);
    freeStack(&sREDO);

   // Închiderea fișierelor
   fclose(fpIn);
   fclose(fpOut);
   return 0;
}