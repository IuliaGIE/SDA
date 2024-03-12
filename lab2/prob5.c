#include <stdio.h>
int cautare_primul(int arr[], int n, int x)
{
    int stanga = 0, dreapta = n - 1, rezultat = -1;
    while (stanga <= dreapta) {
        int mijloc = (stanga + dreapta) / 2;
        if (arr[mijloc] >= x) {
            dreapta = mijloc - 1;
        }
        else {
            stanga = mijloc + 1;
        }
        if (arr[mijloc] == x) {
            rezultat = mijloc;
        }
    }
    return rezultat;
}
int cautare_ultimul(int arr[], int n, int x)
{
    int stanga = 0, dreapta = n - 1, rezultat = -1;
    while (stanga <= dreapta) {
        int mijloc = (stanga + dreapta) / 2;
        if (arr[mijloc] <= x) {
            stanga = mijloc + 1;
        }
        else {
            dreapta = mijloc - 1;
        }
        if (arr[mijloc] == x) {
            rezultat = mijloc;
        }
    }
    return rezultat;
}

int main()
{
    int n, x, i;
    scanf("%d", &n);
    int arr[n];
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    scanf("%d", &x);
    int primul = cautare_primul(arr, n, x);
    int ultimul = cautare_ultimul(arr, n, x);
    if (primul == -1 || ultimul == -1) {
        printf("Numarul %d nu se gaseste in vector.\n", x);
    }
    else {
        printf("Numarul %d apare de %d ori in vector.\n", x, ultimul - primul + 1);
    }
    return 0;
}
