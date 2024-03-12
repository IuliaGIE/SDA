#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Treap
{
    int key, priority;
    struct Treap *left, *right;
} Treap;

Treap *initTreap(int item, int priority)
{
    // Aloca memorie pentru un nou nod și setează valorile sale inițiale
    Treap *root = (Treap *)malloc(sizeof(Treap));
    root->left = NULL;
    root->right = NULL;
    root->key = item;
    root->priority = priority;
    return root;
}

void split(Treap *root, int key, Treap **splitLeft, Treap **splitRight)
{
    if (root == NULL)
    {
        *splitLeft = NULL;
        *splitRight = NULL;
        return;
    }
    if (key < root->key)
    {
        split(root->left, key, splitLeft, &root->left);
        *splitRight = root;
    }
    else
    {
        split(root->right, key, &root->right, splitRight);
        *splitLeft = root;
    }
}

Treap *insert(int key, int priority, Treap *root)
{
    // Inserează un nou nod cu cheia 'key' și prioritatea 'priority' în treapul rădăcină 'root'
    if (root == NULL)
    {
        // Creează un nou nod
        Treap *node = initTreap(key, priority);
        return node;
    }
    // Dacă prioritatea noului nod este mai mare decât prioritatea radacinii
    if (priority > root->priority)
    {
        // Imparte treapul in doua subtreapuri in functie de cheia noului nod
        Treap *splitLeft = NULL;
        Treap *splitRight = NULL;
        split(root, key, &splitLeft, &splitRight);

        // Creeaza noul nod ca radacina a subtreapului din dreapta
        Treap *node = initTreap(key, priority);
        node->left = splitLeft;
        node->right = splitRight;

        return node;
    }

    // Dacă prioritatea noului nod este mai mică sau egală cu prioritatea radacinii
    if (key > root->key)
        root->right = insert(key, priority, root->right);
    else if (key < root->key)
        root->left = insert(key, priority, root->left);

    return root;
}

Treap *delete(int key, Treap *root)
{
    // Caz de bază: dacă rădăcina este NULL, nu există noduri de eliminat
    if (root == NULL)
    {
        return NULL;
    }

    // Caz recursiv: căutăm nodul de eliminat pe ramura corespunzătoare cheii
    if (key < root->key)
    {
        root->left = delete (key, root->left);
    }
    else if (key > root->key)
    {
        root->right = delete (key, root->right);
    }
    else
    { // key == root->key

        // Cazul în care nodul de eliminat nu are niciun fiu
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            root = NULL;

            // Cazul în care nodul de eliminat are doar un fiu (stâng sau drept)
        }
        else if (root->left == NULL)
        {
            Treap *temp = root;
            root = root->right;
            free(temp);
        }
        else if (root->right == NULL)
        {
            Treap *temp = root;
            root = root->left;
            free(temp);

            // Cazul general în care nodul de eliminat are doi fii
        }
        else
        {

            // Găsim fiul cu prioritatea maximă
            Treap *max_child = (root->left->priority > root->right->priority) ? root->left : root->right;

            // Rotim subarborele către stânga/dreapta pentru a aduce fiul maxim pe poziția rădăcinii
            if (max_child == root->left)
            {
                Treap *temp = root->right;
                root->right = temp->left;
                temp->left = root;
                root = temp;
            }
            else
            {
                Treap *temp = root->left;
                root->left = temp->right;
                temp->right = root;
                root = temp;
            }

            // Eliminăm nodul de pe poziția veche a rădăcinii
            root = delete (key, root);
        }
    }

    return root;
}

void inorderTraversal(Treap *root)
{
    if (root != NULL)
    {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

void freeTreap(Treap *root)
{
    if (root != NULL)
    {
        freeTreap(root->left);
        freeTreap(root->right);
        free(root);
    }
}

int main()
{
    Treap *root = NULL;

    // Inserează nodurile în treap
    root = insert(4, 5, root);
    root = insert(2, 10, root);
    root = insert(6, 7, root);
    root = insert(1, 3, root);
    root = insert(3, 8, root);
    root = insert(5, 6, root);
    root = insert(7, 1, root);

    // Afiseaza cheile in ordine crescatoare
    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    // Elimina nodul cu cheia 4 din treap
    root = delete (4, root);

    // Afiseaza cheile in ordine crescatoare dupa eliminarea nodului cu cheia 4
    printf("Inorder Traversal (after deleting key 4): ");
    inorderTraversal(root);
    printf("\n");

    // Elibereaza memoria alocata pentru nodurile din treap
    freeTreap(root);
    return 0;
}
