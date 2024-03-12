#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int nr()
{
    int a;
    printf("Cititi nr de elemente din lista\n");
        scanf("%d",&a);
    return a;
}

void creare (punct *head, int n)
{
    int i;
    punct *hc,*curr;
    hc=head;
    for(i=0;i<n;i++)
    {
        curr=malloc(sizeof(punct));
        if(i==0)
            head->next=curr;
        if(i==n-1)
        {
            hc->next=curr;
            curr->next=head;
        }
        else
        {
            hc->next=curr;
            curr->next=NULL;
        }
        itoa(i,curr->nume_punct,10);
        printf("x=");
         scanf("%lf",&curr->x);
        printf("\ny=");
            scanf("%lf",&curr->y);
        hc=hc->next;
    }
}

void afisare(punct *head)
{
    punct *t;
    for(t=head->next;t!=head;t=t->next)
    {
        printf("%s\n%lf\n%lf\n\n",t->nume_punct,t->x,t->y);
    }
}