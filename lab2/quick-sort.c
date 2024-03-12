#include <stdio.h>

// Functie pentru interschimbarea a doua elemente din vector
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Functie pentru partitionarea vectorului si returnarea pivotului
int partition(int arr[], int low, int high)
{
    int pivot = arr[high]; // pivotul este ultimul element
    int i = low - 1; // indexul primului element
    for (int j = low; j <= high - 1; j++) {
        // daca elementul curent este mai mic sau egal cu pivotul
        if (arr[j] <= pivot) {
            i++; // incrementam indexul primului element
            swap(&arr[i], &arr[j]); // interschimbam elementele
        }
    }
    swap(&arr[i + 1], &arr[high]); // plasam pivotul in pozitia corecta
    return i + 1;
}

// Functie principala pentru QuickSort
void quickSort(int arr[], int low, int high)
{
    if (low < high) {
        int pivot = partition(arr, low, high); // pivotul
        quickSort(arr, low, pivot - 1); // sortam sub-vectorul stang
        quickSort(arr, pivot + 1, high); // sortam sub-vectorul drept
    }
}

// Functie pentru afisarea vectorului sortat
void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int n, i;
    printf("Introduceti dimensiunea vectorului: ");
    scanf("%d", &n);
    int arr[n];
    printf("Introduceti elementele vectorului: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    quickSort(arr, 0, n - 1);
    printf("Vectorul sortat: ");
    printArray(arr, n);
    return 0;
}
