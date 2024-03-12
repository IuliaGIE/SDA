#include <stdio.h>

int binarySearchFirst(int arr[], int low, int high, int x);
int binarySearchLast(int arr[], int low, int high, int x);

int main() {
    int arr[] = {1, 2, 3, 3, 3, 4, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 3;
    int first = binarySearchFirst(arr, 0, n-1, x);
    int last = binarySearchLast(arr, 0, n-1, x);
    int count = last - first + 1;
    printf("%d apare de %d ori in vector.\n", x, count);
    return 0;
}

int binarySearchFirst(int arr[], int low, int high, int x) {
    if (high >= low) {
        int mid = low + (high - low) / 2;
        if ((mid == 0 || x > arr[mid - 1]) && arr[mid] == x) {
            return mid;
        }
        else if (x > arr[mid]) {
            return binarySearchFirst(arr, mid + 1, high, x);
        }
        else {
            return binarySearchFirst(arr, low, mid - 1, x);
        }
    }
    return -1;
}

int binarySearchLast(int arr[], int low, int high, int x) {
    if (high >= low) {
        int mid = low + (high - low) / 2;
        if ((mid == high || x < arr[mid + 1]) && arr[mid] == x) {
            return mid;
        }
        else if (x < arr[mid]) {
            return binarySearchLast(arr, low, mid - 1, x);
        }
        else {
            return binarySearchLast(arr, mid + 1, high, x);
        }
    }
    return -1;
}
