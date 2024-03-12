// Giuroiu Iulia Elena - 313CC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

// coada de comenzi
typedef struct
{
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
typedef struct StackNode
{
    node *index;
    struct StackNode *next;
} StackNode;

typedef struct Stack
{
    StackNode *head;
    long size;
} Stack;

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
    list->sentinel->next->data = '#';
    list->finger = list->tail;
    list->len = 0;
}

// eliberarea bandei
void freeList(TDoubleLinkedList *list)
{
    node *current = list->sentinel;
    node *temp;
    while (current != NULL)
    {
        temp = current;
        current = current->next;
        list->sentinel->next = current;
        free(temp);
    }
    list = NULL;
}

// alocarea de memorie pt coada
void initQueue(Queue *q, int size)
{
    q->items = (char **)malloc(size * sizeof(char *));
    q->size = size;
    q->front = 0;
    q->rear = -1;
}

// functia de init stiva
void initStack(Stack *s)
{
    s->head = (StackNode *)malloc(sizeof(StackNode));
    s->head->index = NULL;
    s->head->next = NULL;
    s->size = 0;
}

// adaugarea in stiva
void push(Stack *s, node *index)
{
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    newNode->index = index;
    newNode->next = s->head;
    s->head = newNode;
}

// scoaterea din stiva
node *pop(Stack *s)
{
    if (s->head == NULL)
    {
        return NULL;
    }
    StackNode *top = s->head;
    node *index = top->index;
    s->head = top->next;
    free(top);
    return index;
}

// golirea stivei
void emptyStack(Stack *stack)
{
    while (stack->head != NULL)
    {
        StackNode *temp = stack->head;
        stack->head = stack->head->next;
        free(temp);
    }
}

// afisarea elementelor din banda
void SHOW(FILE *fpOut, TDoubleLinkedList *list)
{
    node *current = list->sentinel->next;
    while (current != NULL)
    {
        if (current == list->finger)
            fprintf(fpOut, "|%c|", current->data);
        else
            fprintf(fpOut, "%c", current->data);
        current = current->next;
    }
    fprintf(fpOut, "\n");
}

// afiseaza elementul curent
void SHOW_CURRENT(FILE *fpOut, TDoubleLinkedList *list)
{
    if (list->finger)
        fprintf(fpOut, "%c\n", list->finger->data);
}

// adaugare element
void add(TDoubleLinkedList *list, char item)
{
    node *nnode = (node *)malloc(sizeof(node));
    nnode->data = item;
    nnode->next = NULL;
    nnode->prev = list->finger;
    if (list->finger != NULL)
        list->finger->next = nnode;
    else
        list->tail = nnode;
    list->finger = nnode;
}

// muta la stanga in banda
void MOVE_LEFT(TDoubleLinkedList *list)
{
    node *current = list->finger;
    if (current != list->sentinel->next)
        list->finger = current->prev;
}

// muta la dreapta in banda
void MOVE_RIGHT(TDoubleLinkedList *list)
{
    if (list->finger->next != NULL)
        list->finger = list->finger->next;
    else if (list->finger->next == NULL)
    {
        add(list, '#');
    }
}

// scrie un nou caracter in pozitia curenta
void WRITE(TDoubleLinkedList *list, char c)
{
    list->finger->data = c;
}

// insereaza la stanga un caracter *modificat cu fisier
void INSERT_LEFT(FILE *fpOut, TDoubleLinkedList *list, char c)
{
    node *current = list->finger;
    node *new_node = (node *)malloc(sizeof(node));
    new_node->data = c;
    if (current == list->sentinel->next)
        fprintf(fpOut, "ERROR\n");
    else
    {
        // exista o pozitie curenta, deci inseram inaintea ei
        new_node->next = list->finger;
        new_node->prev = list->finger->prev;
        if (list->finger->prev != NULL)
        {
            list->finger->prev->next = new_node;
        }
        else
        {
            list->sentinel = new_node;
        }
        list->finger->prev = new_node;
        list->finger = new_node;
    }
}

// insereaza la dreapta un caracter
void INSERT_RIGHT(TDoubleLinkedList *list, char c)
{
    node *new_node = (node *)malloc(sizeof(node)); // alocă memorie pentru noul nod
    new_node->data = c;                            // setează datele pentru noul nod
    if (list->finger->next == NULL)
    {
        add(list, c);
    }
    else
    {
        new_node->next = list->finger->next;
        new_node->prev = list->finger;
        if (list->finger->next != NULL)
        {
            list->finger->next->prev = new_node;
        }
        list->finger->next = new_node;
        // actualizarea pozitiei curente in lista
        list->finger = new_node;
    }
}

// cauta la stanga un caracter <c>
void MOVE_LEFT_CHAR(FILE *fpOut, TDoubleLinkedList *list, char c)
{
    node *current = list->finger;
    int ok = 0;
    while (current != list->sentinel->prev)
    {
        if (current->data == c)
        {
            ok = 1;
            list->finger = current;
            break;
        }
        current = current->prev;
    }
    if (ok == 0)
        fprintf(fpOut, "ERROR\n");
}

// cauta la dreapta un caracter <c>
void MOVE_RIGHT_CHAR(TDoubleLinkedList *list, char c)
{
    node *current = list->finger;
    int ok = 0;
    while (current != NULL)
    {
        if (current->data == c)
        {
            ok = 1;
            list->finger = current;
            break;
        }
        current = current->next;
    }
    if (ok == 0)
        add(list, '#');
}

// comanda de UNDO
node *UNDO(TDoubleLinkedList *list, Stack *s)
{
    node *index = pop(s);
    list->finger = index;
    return index;
}

// comanda de REDO
node *REDO(TDoubleLinkedList *list, Stack *s)
{
    node *index = pop(s);
    list->finger = index;
    return index;
}

// adauga in coada de comenzi
void enqueue(Queue *q, char *item)
{
    q->rear++;
    q->items[q->rear] = (char *)malloc(strlen(item) + 1);
    strcpy(q->items[q->rear], item);
}

// scoate din coada de comenzi
char *dequeue(Queue *q)
{
    if (q->rear < q->front)
    {
        printf("Coada este goala.\n");
        return NULL;
    }
    char *item = q->items[q->front];
    q->front++;
    return item;
}

int main()
{
    FILE *fpIn, *fpOut;
    Queue q;
    Stack sUNDO, sREDO;
    char buffer[MAX_SIZE];
    int n, i;
    fpIn = fopen("tema1.in", "r");
    fpOut = fopen("tema1.out", "w");

    // initializarea listei
    TDoubleLinkedList *list;
    list = (TDoubleLinkedList *)malloc(sizeof(TDoubleLinkedList));
    init(list);

    // verificare dacă fișierele pot fi deschise
    if (fpIn == NULL || fpOut == NULL)
    {
        printf("Eroare la deschiderea fișierelor.");
        return -1;
    }

    // citirea numarului n
    fscanf(fpIn, "%d", &n);

    // initializarea cozii
    initQueue(&q, n);
    // initializarea stivelor
    initStack(&sREDO);
    initStack(&sUNDO);
    fgets(buffer, MAX_SIZE, fpIn);
    char c;
    // citirea urmatoarelor n linii si adaugarea lor in coada
    for (i = 0; i < n; i++)
    {
        fgets(buffer, MAX_SIZE, fpIn);
        if (strstr(buffer, "EXECUTE") != NULL)
        {
            // scoate prima comanda din coada
            char *item = dequeue(&q);
            if (strstr(item, "MOVE_RIGHT_CHAR") != NULL)
            {
                c = item[16];
                MOVE_RIGHT_CHAR(list, c);
                emptyStack(&sUNDO);
                emptyStack(&sREDO);
                initStack(&sREDO);
                initStack(&sUNDO);
            }
            else if (strstr(item, "MOVE_LEFT_CHAR") != NULL)
            {
                c = item[15];
                MOVE_LEFT_CHAR(fpOut, list, c);
                emptyStack(&sUNDO);
                emptyStack(&sREDO);
                initStack(&sREDO);
                initStack(&sUNDO);
            }
            else if (strstr(item, "MOVE_LEFT") != NULL)
            {
                push(&sUNDO, list->finger);
                MOVE_LEFT(list);
            }
            else if (strstr(item, "MOVE_RIGHT") != NULL)
            {
                push(&sUNDO, list->finger);
                MOVE_RIGHT(list);
            }
            else if (strstr(item, "WRITE") != NULL)
            {
                c = item[6];
                WRITE(list, c);
                emptyStack(&sUNDO);
                emptyStack(&sREDO);
                initStack(&sREDO);
                initStack(&sUNDO);
            }
            else if (strstr(item, "INSERT_RIGHT") != NULL)
            {
                c = item[13];
                INSERT_RIGHT(list, c);
                emptyStack(&sUNDO);
                emptyStack(&sREDO);
                initStack(&sREDO);
                initStack(&sUNDO);
            }
            else if (strstr(item, "INSERT_LEFT") != NULL)
            {
                c = item[12];
                INSERT_LEFT(fpOut, list, c);
                emptyStack(&sUNDO);
                emptyStack(&sREDO);
                initStack(&sREDO);
                initStack(&sUNDO);
            }
        }
        else if (strstr(buffer, "SHOW_CURRENT") != NULL)
        {
            // afiseaza carcterul curent
            SHOW_CURRENT(fpOut, list);
        }
        else if (strstr(buffer, "SHOW") != NULL)
        {
            // afiseaza lista
            SHOW(fpOut, list);
        }
        else if (strstr(buffer, "UNDO") != NULL)
        {
            // face undo
            node *redo = UNDO(list, &sUNDO);
            push(&sREDO, redo);
        }
        else if (strstr(buffer, "REDO") != NULL)
        {
            // face redo
            node *undo = REDO(list, &sUNDO);
            push(&sUNDO, undo);
        }
        else
            enqueue(&q, buffer); // adauga in coada de comenzi tipul UPDATE
    }

    // eliberarea memoriei alocate pentru fiecare item din coada
    for (i = q.front; i <= q.rear; i++)
    {
        free(q.items[i]);
    }

    // eliberam banda
    freeList(list);
    free(list);

    // eliberez stivele
    emptyStack(&sUNDO);
    emptyStack(&sREDO);

    // Închiderea fișierelor
    fclose(fpIn);
    fclose(fpOut);
    return 0;
}