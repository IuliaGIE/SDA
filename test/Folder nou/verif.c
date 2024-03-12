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
    node *finger;
    int len;
} TDoubleLinkedList;

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
void createQueue(Queue *q, int size) {
   q->items = (char **)malloc(size * sizeof(char *));
   q->size = size;
   q->front = 0;
   q->rear = -1;
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

// e modificata fata de fisierul test.c
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
    if(list->finger->next == NULL){
        add(list, '#');
    } 
}

// scrie un nou caracter in pozitia curenta
void WRITE(TDoubleLinkedList *list, char c){
   list->finger->data = c;
}

// insereaza la stanga un caracter *modificat cu fisier
void INSERT_LEFT(FILE *fpOut, TDoubleLinkedList *list, char c){
    node *current = list->finger;
    if(current == list->sentinel->next)
        fprintf(fpOut, "ERROR\n");
    else{
        list->finger = list->finger->prev;
        list->finger->data = c;
    }
}

// insereaza la dreapta un caracter
void INSERT_RIGHT(TDoubleLinkedList *list, char c){
    if(list->finger->next != NULL){
        list->finger = list->finger->next;
        list->finger->data = c;
    }
    else{
        //i think it's done here
        add(list, c);
        ///list->finger = list->finger->next;
        //list->finger->data = c;
    }
}

// cauta la stanga un caracter <c>
void MOVE_LEFT_CHAR(FILE *fpOut, TDoubleLinkedList *list, char c){
    int i;
}

// cauta la dreapta un caracter <c>
void MOVE_RIGHT_CHAR(TDoubleLinkedList *list, char c){
    int i;
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

int main() {
   FILE *fpIn, *fpOut;
   Queue q;
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
   createQueue(&q, n);
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
            //MOVE_RIGHT_CHAR();
            c = item[16];
            printf("%c\n", c);
            //printf("%s", item);
        }
        else if(strstr(item, "MOVE_LEFT_CHAR")!= NULL){
            //MOVE_LEFT_CHAR();
            c = item[15];
            printf("%c\n", c);
            //printf("%s", item);
        }
        else if(strstr(item, "MOVE_LEFT")!= NULL){
            MOVE_LEFT(list);
            //printf("%s", item);
        }
        else if(strstr(item, "MOVE_RIGHT")!= NULL)
        {
            MOVE_RIGHT(list);
            //printf("%s", item);
        }
        else if(strstr(item, "WRITE")!= NULL)
        {
            //char c[2];
            c = item[6];
            WRITE(list, c);
            //printf("%c\n", item[6]);
        }
        else if(strstr(item, "INSERT_RIGHT")!= NULL)
        {
            c = item[13];
            //printf("%c\n", c);
            INSERT_RIGHT(list, c);
            //printf("%s", item);
        }
        else if(strstr(item, "INSERT_LEFT")!= NULL)
        {
            c = item[12];
            //printf("%c\n", c);
            INSERT_LEFT(fpOut, list, c);
            //printf("%s", item);
        }
        //SHOW(fpOut, list);
      }
      else if(strstr(buffer, "SHOW_CURRENT") != NULL)
      {
        // afiseaza carcterul curent
        SHOW_CURRENT(fpOut, list);
        //printf("Afiseaza caracterul curent\n");
      }
      else if(strstr(buffer, "SHOW") != NULL)
      {
        // afiseaza lista
        SHOW(fpOut, list);
        //printf("Afiseaza lista\n");
      }
      else if(strstr(buffer, "UNDO") != NULL)
      {
        // Face undo
        // UNDO()
        printf("UNDO\n");
      }
      else if(strstr(buffer, "REDO") != NULL)
      {
        // Face redo
        // redo()
        printf("REDO\n");
      }
      else enqueue(&q, buffer);
   }

   // Scrierea cozii in fisierul "tema1.out"
   while (q.front <= q.rear) {
      char *item = dequeue(&q);
      fprintf(fpOut, "%s", item);
   }

   // Eliberarea memoriei alocate pentru fiecare item din coada
   for (i = q.front; i <= q.rear; i++) {
      free(q.items[i]);
   }

   // eliberam banda
   freeList(list);
   free(list);

   // Închiderea fișierelor
   fclose(fpIn);
   fclose(fpOut);
   return 0;
}