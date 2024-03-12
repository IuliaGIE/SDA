#include <stdlib.h>
#include "Stack.h"

int main(){
    Stack* stack = createStack();
    // Adaugam elemente in stiva
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);

    // Afisam elementul din varful stivei
    printf("Elementul din varful stivei este: %d\n", top(stack));

    // Scoatem elemente din stiva si le afisam
    while (!isStackEmpty(stack)) {
        printf("%d ", pop(stack));
    }
    printf("\n");

    // Distruge stiva
    destroyStack(stack);

    return 0;
}
