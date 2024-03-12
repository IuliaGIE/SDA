#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Trie{
    int count, nrfii;
    struct Trie* child[26];
} Trie;

Trie* init() {
    Trie* node = (Trie*)malloc(sizeof(Trie));
    node->count = 0;
    node->nrfii = 0;
    for(int i=0; i<26; i++)
        node->child[i] = NULL;
    return node;
}

void insert(Trie* root, char* word) {
    Trie* node = root;
    int len = strlen(word);
    for(int i=0; i<len; i++) {
        int index = word[i] - 'a';
        if(node->child[index] == NULL) {
            node->child[index] = init();
            node->nrfii++;
        }
        node = node->child[index];
    }
    node->count++;
}

void freeTrie(Trie* root) {
    if(root == NULL)
        return;
    for(int i=0; i<26; i++) {
        freeTrie(root->child[i]);
    }
    free(root);
}

void printTrie(Trie* root, char word[], int pos) {
    if(root == NULL)
        return;
    if(root->count > 0) {
        word[pos] = '\0';
        printf("%s\n", word);
    }
    for(int i=0; i<26; i++) {
        if(root->child[i] != NULL) {
            word[pos] = 'a' + i;
            printTrie(root->child[i], word, pos+1);
        }
    }
}

void searchPrefix(Trie* root, char* prefix, char* word, int pos) {
    if(root == NULL)
        return;
    if(*prefix == '\0') {
        if(root->count > 0) {
            word[pos] = '\0';
            printf("%s\n", word);
        }
        printTrie(root, word, pos);
        return;
    }
    int index = *prefix - 'a';
    if(root->child[index] == NULL)
        return;
    word[pos] = *prefix;
    searchPrefix(root->child[index], prefix+1, word, pos+1);
}

int main() {
    FILE* in = fopen("lab7.in", "r");
    if(in == NULL) {
        printf("Eroare la deschiderea fisierului lab7.in");
        return 1;
    }

    // Citim N si M din fisier
    int n, m;
    fscanf(in, "%d %d", &n, &m);

    // Citim cuvintele si le inseram in Trie
    Trie* root = init();
    char word[100];
    for(int i=0; i<n; i++) {
        fscanf(in, "%s", word);
        insert(root, word);
    }

    // Citim prefixele si cautam cuvintele care incep cu acele prefixe
        char prefix[100];
    for(int i=0; i<m; i++) {
        fscanf(in, "%s", prefix);
        printf("Cuvintele care incep cu prefixul \"%s\" sunt:\n", prefix);
        searchPrefix(root, prefix, word, 0);
        printf("\n");
    }

    // Eliberam memoria alocata pentru Trie
    freeTrie(root);

    // Inchidem fisierul de intrare
    fclose(in);

    return 0;
}

