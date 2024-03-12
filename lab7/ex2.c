#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Trie{
    int count, nrfii;
    struct Trie* child[26];
} Trie;

// Initializare Trie
Trie* init() {
    Trie* node = (Trie*) malloc(sizeof(Trie));
    node->count = 0;
    node->nrfii = 0;
    for(int i=0; i<26; i++)
        node->child[i] = NULL;
    return node;
}

// Inserare cuvant in Trie
void insert(Trie* root, char* word) {
    Trie* node = root;
    for(int i=0; word[i]!='\0'; i++) {
        int index = word[i] - 'a';
        if(node->child[index] == NULL) {
            node->child[index] = init();
            node->nrfii++;
        }
        node = node->child[index];
    }
    node->count++;
}

// Stergere cuvant din Trie
void delete(Trie* root, char* word) {
    Trie* node = root;
    for(int i=0; word[i]!='\0'; i++) {
        int index = word[i] - 'a';
        if(node->child[index] == NULL)
            return; // Cuvantul nu exista in Trie
        node = node->child[index];
    }
    if(node->count > 0) {
        node->count--;
        return;
    }
    // Stergem nodul daca nu mai are copii si count = 0
    node->nrfii--;
    for(int i=0; i<26; i++) {
        if(node->child[i] != NULL) {
            return; // Nu putem sterge nodul inca
        }
    }
    free(node);
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

// Eliberare memorie Trie
void freeTrie(Trie* root) {
    if(root == NULL)
        return;
    for(int i=0; i<26; i++)
        freeTrie(root->child[i]);
    free(root);
}

int main() {
    Trie* root = init();
    char word[100];

    // Inseram cuvinte in Trie
    printf("Introduceti cuvinte (terminati cuvantul \"stop\" pentru a opri):\n");
    while(1) {
        scanf("%s", word);
        if(strcmp(word, "stop") == 0)
            break;
        insert(root, word);
    }

    // Afisam continutul Trie
    printf("Continutul Trie:\n");
    printTrie(root, word, 0);

    // Stergem un cuvant din Trie
    printf("Introduceti cuvantul de sters din Trie:\n");
    scanf("%s", word);
    delete(root, word);

    // Afisam continutul Trie
    printf("Continutul Trie:\n");
    printTrie(root, word, 0);
    
    // Eliberam memoria pentru structura Trie
    freeTrie(root);

    return 0;
}
