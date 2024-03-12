#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BSTree
{
    int key;
    struct BSTree *left, *right, *father;
} BSTree;

BSTree *initBSTree(int item)
{
    BSTree *root = (BSTree *)malloc(sizeof(BSTree));
    root->left = NULL;
    root->right = NULL;
    root->father = NULL;
    root->key = item;
    return root;
}

BSTree *insert(int item, BSTree *root)
{
    if (root == NULL)
        return initBSTree(item);
    if (item > root->key)
    {
        BSTree *node = insert(item, root->right);
        node->father = root;
        root->right = node;
    }
    else if (item < root->key)
    {
        BSTree *node = insert(item, root->left);
        node->father = root;
        root->left = node;
    }
    return root;
}

void inorder(BSTree *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

void preorder(BSTree *root)
{
    if (root == NULL)
        return;
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

void postorder(BSTree *root)
{
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->key);
}

BSTree *search(BSTree *root, int x)
{
    if (root == NULL || root->key == x)
        return root;
    if (x > root->key)
        return search(root->right, x);
    return search(root->left, x);
}

BSTree *findMinim(BSTree *root)
{
    if (root == NULL)
        return NULL;
    if (root->left == NULL)
        return root;
    return findMinim(root->left);
}

BSTree *findMaxim(BSTree *root)
{
    if (root == NULL)
        return NULL;
    if (root->right == NULL)
        return root;
    return findMaxim(root->right);
}

int search_prev(BSTree *root, int x)
{
    BSTree *node = search(root, x);
    if (node == NULL)
        return -1;
    if (node->left != NULL)
        return findMaxim(node->left)->key;
    BSTree *parent = node->father;
    while (parent != NULL && node == parent->left)
    {
        node = parent;
        parent = node->father;
    }
    if (parent != NULL)
        return parent->key;
    return -1;
}

int search_next(BSTree *root, int x)
{
    BSTree *node = search(root, x);
    if (node == NULL)
        return -1;
    if (node->right != NULL)
        return findMinim(node->right)->key;
    BSTree *parent = node->father;
    while (parent != NULL && node == parent->right)
    {
        node = parent;
        parent = node->father;
    }
    if (parent != NULL)
        return parent->key;
    return -1;
}

void free_tree(BSTree *root)
{
    if (root == NULL)
    {
        return;
    }

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main()
{
    BSTree *tree = NULL;
    // inserarea unor valori in arbore
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

    // afisarea arborelui in inordine
    printf("Inordine: ");
    inorder(tree);
    printf("\n");

    // afisarea arborelui in preordine
    printf("Preordine: ");
    preorder(tree);
    printf("\n");

    // afisarea arborelui in postordine
    printf("Postordine: ");
    postorder(tree);
    printf("\n");

    // cautarea valorii maxime mai mici decat 9
    int prev = search_prev(tree, 9);
    if (prev != -1)
    {
        printf("Valoarea maxima mai mica decat 9: %d\n", prev);
    }
    else
    {
        printf("Nu exista valori mai mici decat 9 in arbore\n");
    }

    // cautarea valorii minime mai mari decat 7
    int next = search_next(tree, 7);
    if (next != -1)
    {
        printf("Valoarea minima mai mare decat 7: %d\n", next);
    }
    else
    {
        printf("Nu exista valori mai mari decat 7 in arbore\n");
    }

    // eliberarea memoriei ocupate de arbore
    free_tree(tree);

    return 0;
}