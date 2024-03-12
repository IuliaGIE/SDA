#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main()
{
    int n;
    punct *head=NULL;
    head=malloc(sizeof(punct));
    head->next=NULL;
    n=nr();
    creare(head,n);
    afisare(head);
    return 0;
}