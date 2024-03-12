#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BSTree
{
    int key;
    struct BSTree *left, *right;
} BSTree;

BSTree *initBSTree(int item)
{
    // Aloca memorie pentru un nou nod si seteaza valorile sale initiale
    BSTree *root = (BSTree *)malloc(sizeof(BSTree));
    root->left = NULL;
    root->right = NULL;
    root->key = item;
    return root;
}

BSTree *insert(int item, BSTree *root)
{
    // Insereaza un nou nod cu valoarea 'item' in arborele radacina 'root'
    if (root == NULL)
        return initBSTree(item);
    if (item > root->key)
        root->right = insert(item, root->right);
    else if (item < root->key)
        root->left = insert(item, root->left);
    return root;
}

BSTree *findMinim(BSTree *root)
{
    // Gaseste si returneaza nodul cu cea mai mica valoare din arborele radacina 'root'
    if (root == NULL)
        return NULL;
    if (root->left == NULL)
        return root;
    return findMinim(root->left);
}

BSTree *search(int item, BSTree *root)
{
    // Cauta si returneaza nodul cu valoarea 'item' in arborele radacina 'root'
    if (root == NULL || root->key == item)
        return root;
    if (item > root->key)
        return search(item, root->right);
    else
        return search(item, root->left);
}

BSTree *delete(int item, BSTree *root)
{
    // Sterge nodul cu valoarea 'item' din arborele radacina 'root'
    if (root == NULL)
        return root;
    if (item < root->key)
        root->left = delete (item, root->left);
    else if (item > root->key)
        root->right = delete (item, root->right);
    else
    {
        // nodul cu valoarea 'item' a fost gasit
        if (root->left == NULL)
        {
            BSTree *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            BSTree *temp = root->left;
            free(root);
            return temp;
        }
        // nodul are doi succesori
        BSTree *temp = findMinim(root->right);
        root->key = temp->key;
        root->right = delete (temp->key, root->right);
    }
    return root;
}

void freeBSTree(BSTree *root)
{
    // Elibereaza memoria alocata pentru nodurile arborelui radacina 'root'
    if (root != NULL)
    {
        freeBSTree(root->left);
        freeBSTree(root->right);
        free(root);
    }
}

int height(BSTree *root)
{
    // Calculeaza si returneaza inaltimea arborelui radacina 'root'
    if (root == NULL)
        return -1;
    int left_height = height(root->left);
    int right_height = height(root->right);
    if (left_height > right_height)
        return left_height + 1;
    else
        return right_height + 1;
}

int main()
{
    BSTree *tree = NULL;
    tree = insert(10, tree);
    tree = insert(7, tree);
    tree = insert(13, tree);
    tree = insert(12, tree);
    tree = insert(2, tree);
    tree = insert(4, tree);
    tree = insert(9, tree);
    tree = insert(8, tree);
    tree = insert(3, tree);
    tree = insert(1, tree);

    // Testeaza functia search
    BSTree *found = search(13, tree);
    if (found != NULL)
        printf("Nodul cu valoarea 13 a fost gasit.\n");

    // Testeaza functia delete
    tree = delete (4, tree);

    // Testeaza functia height
    int h = height(tree);
    printf("Inaltimea arborelui este: %d\n", h);

    // Elibereaza memoria alocata pentru arbore
    freeBSTree(tree);

    return 0;
}
