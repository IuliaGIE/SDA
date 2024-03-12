#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Treap {
    int key, priority;
    struct Treap *left, *right;
} Treap;

Treap *createTreapNode(int key, int priority) {
    Treap *newNode = (Treap *)malloc(sizeof(Treap));
    newNode->key = key;
    newNode->priority = priority;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Treap *rotateRight(Treap *y) {
    Treap *x = y->left;
    Treap *T2 = x->right;
    x->right = y;
    y->left = T2;
    return x;
}

Treap *rotateLeft(Treap *x) {
    Treap *y = x->right;
    Treap *T2 = y->left;
    y->left = x;
    x->right = T2;
    return y;
}

Treap *insert(Treap *root, int key, int priority) {
    if (root == NULL) {
        return createTreapNode(key, priority);
    }
    if (key < root->key) {
        root->left = insert(root->left, key, priority);
        if (root->left->priority > root->priority) {
            root = rotateRight(root);
        }
    } else if (key > root->key) {
        root->right = insert(root->right, key, priority);
        if (root->right->priority > root->priority) {
            root = rotateLeft(root);
        }
    }
    return root;
}

Treap *delete(Treap *root, int key) {
    if (root == NULL) {
        return root;
    }
    if (key < root->key) {
        root->left = delete(root->left, key);
    } else if (key > root->key) {
        root->right = delete(root->right, key);
    } else {
        if (root->left == NULL) {
            Treap *temp = root->right;
            free(root);
            root = temp;
        } else if (root->right == NULL) {
            Treap *temp = root->left;
            free(root);
            root = temp;
        } else if (root->left->priority < root->right->priority) {
            root = rotateLeft(root);
            root->left = delete(root->left, key);
        } else {
            root = rotateRight(root);
            root->right = delete(root->right, key);
        }
    }
    return root;
}

void inorderTraversal(Treap *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

void freeTreap(Treap *root) {
    if (root != NULL) {
        freeTreap(root->left);
        freeTreap(root->right);
        free(root);
    }
}

int main() {
    srand(time(0));

    Treap *root = NULL;

    // Inserează nodurile în treap
    root = insert(root, 4, rand());
    root = insert(root, 2, rand());
    root = insert(root, 6, rand());
    root = insert(root, 1, rand());
    root = insert(root, 3, rand());
    root = insert(root, 5, rand());
    root = insert(root, 7, rand());

    // Afișează cheile în ordine crescătoare
    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    // Elimină nodul cu cheia 4 din treap
    root = delete(root, 4);

    // Afișează cheile în ordine crescătoare după eliminarea nodului cu cheia 4
    printf("Inorder Traversal (after deleting key 4): ");
    inorderTraversal(root);
    printf("\n");

    // Eliberează memoria alocată pentru nodurile din treap
    freeTreap(root);

    return 0;
}
