#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nod {
    char *val;
    struct nod *next;
} nod;

typedef struct hashtable {
    nod **Table;
    int nr_buckets;
    int (*hfunc)(char*);
    int size;
} hashtable;

// Funcție pentru a crea un hashtable
hashtable* createHashtable(int nr_buckets, int (*hfunc)(char*)) {
    hashtable *h = (hashtable*)malloc(sizeof(hashtable));
    h->Table = (nod**)malloc(nr_buckets * sizeof(nod*));
    h->nr_buckets = nr_buckets;
    h->hfunc = hfunc;
    h->size = 0;

    for (int i = 0; i < nr_buckets; i++) {
        h->Table[i] = NULL;
    }

    return h;
}

// Funcție pentru a insera un element în hashtable
void insert(hashtable *h, char *val) {
    int bucket = h->hfunc(val);

    nod *n = (nod*)malloc(sizeof(nod));
    n->val = strdup(val);
    n->next = h->Table[bucket];
    h->Table[bucket] = n;

    h->size++;
}

// Funcție pentru a căuta un element în hashtable
int find(hashtable *h, char *val) {
    int bucket = h->hfunc(val);

    nod *n = h->Table[bucket];
    while (n != NULL) {
        if (strcmp(n->val, val) == 0) {
            return 1; // Elementul a fost găsit
        }
        n = n->next;
    }

    return 0; // Elementul nu a fost găsit
}

// Funcție pentru a șterge un element din hashtable
void delete(hashtable *h, char *val) {
    int bucket = h->hfunc(val);

    nod *prev = NULL;
    nod *curr = h->Table[bucket];
    while (curr != NULL) {
        if (strcmp(curr->val, val) == 0) {
            if (prev == NULL) {
                h->Table[bucket] = curr->next;
            } else {
                prev->next = curr->next;
            }

            free(curr->val);
            free(curr);

            h->size--;
            return;
        }

        prev = curr;
        curr = curr->next;
    }
}

// Funcție pentru a afișa hashtable-ul
void printHashtable(hashtable *h) {
    for (int i = 0; i < h->nr_buckets; i++) {
        printf("Bucket %d:", i);

        nod *n = h->Table[i];
        while (n != NULL) {
            printf(" %s", n->val);
            n = n->next;
        }

        printf("\n");
    }
}

// Funcție pentru a elibera memoria alocată pentru hashtable
void destroyHashtable(hashtable *h) {
    for (int i = 0; i < h->nr_buckets; i++) {
        nod *n = h->Table[i];
        while (n != NULL) {
            nod *next = n->next;
            free(n->val);
            free(n);
            n = next;
        }
    }

    free(h->Table);
    free(h);
}
// Funcție hash simplă care adună valorile ASCII ale caracterelor
int hashFunction(char *val) {
    int sum = 0;
    for (int i = 0; i < strlen(val); i++) {
        sum += val[i];
    }
    return sum % 10; // Numărul de bucket-uri este 10
}

int main() {
    hashtable *h = createHashtable(10, hashFunction);

    insert(h, "apple");
    insert(h, "banana");
    insert(h, "orange");
    insert(h, "grape");
    insert(h, "watermelon");

    printf("Hashtable after insertions:\n");
    printHashtable(h);
    printf("Size: %d\n", h->size);

    printf("\n");

    printf("Find 'apple': %d\n", find(h, "apple"));
    printf("Find 'grape': %d\n", find(h, "grape"));
    printf("Find 'melon': %d\n", find(h, "melon"));

    printf("\n");

    delete(h, "banana");
    delete(h, "watermelon");

    printf("Hashtable after deletions:\n");
    printHashtable(h);
    printf("Size: %d\n", h->size);

    destroyHashtable(h);

    return 0;
}

