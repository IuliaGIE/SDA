#ifndef list
#define list

typedef struct punct{
    char *nume_punct;
    double x, y;
    struct punct *next;
}punct;

int nr();
void creare (punct *head, int n);
void afisare(punct *head);

#endif // list