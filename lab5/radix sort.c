#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_INPUT_LEN 256

typedef int Item;
#include "Queue.h"

void printArray(int *arr, int len)
{
    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);
}

int arrayMaximum(const int *arr, int len)
{
    int max = arr[0];
    for (int i = 1; i < len; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

int getNumberOfDigits(int num)
{
    int digits = 0;
    while (num)
    {
        num = num / 10;
        digits++;
    }
    return digits;
}

void radixSort(int *arr, int len)
{

    // 1. Initialize queues for each digit, i.e., our buckets
    Queue queues[10];
    for (int i = 0; i < 10; i++)
        queues[i] = createQueue();

    // 2. Compute the number of iterations required to sort the array
    int max = arrayMaximum(arr, len);
    int numDigits = getNumberOfDigits(max);

    // Radix sort
    // 3. Iterate over the maximum number of digits
    for (int digit = 1; digit <= numDigits; digit++)
    {

        // 3a. Place the number in a bucket according to its digit
        for (int i = 0; i < len; i++)
        {
            int bucketIndex = (arr[i] / (int)pow(10, digit - 1)) % 10;
            enqueue(&queues[bucketIndex], arr[i]);
        }

        // 3b. Re-construct the array by using each bucket in order
        int index = 0;
        for (int i = 0; i < 10; i++)
        {
            while (!isEmpty(&queues[i]))
            {
                arr[index++] = dequeue(&queues[i]);
            }
        }
    }

    // 4. Destroy queues
    for (int i = 0; i < 10; i++)
        destroyQueue(&queues[i]);
}

int main(void)
{

    int len;
    char fileBuffer[MAX_INPUT_LEN];
    FILE *inputFile = fopen("input-radix-sort.csv", "r");
    if (inputFile == NULL)
        return 1;

    int capacity = MAX_INPUT_LEN;
    int *arr = (int *)malloc(capacity * sizeof(int));

    int count = 0;
    while (fgets(fileBuffer, MAX_INPUT_LEN, inputFile) != NULL)
    {
        fileBuffer[strcspn(fileBuffer, "\r\n")] = 0;
        len = strlen(fileBuffer);
        if (len == 0)
            break;

        char *token = strtok(fileBuffer, ",\n");
        if (token == NULL)
            return 1;
        len = 0;
        arr[len++] = atoi(token);
        while (token != NULL)
        {
            if (len == capacity)
            {
                capacity <<= 1;
                arr = realloc(arr, capacity * sizeof(int));
            }

            token = strtok(NULL, ",\r\n");
            if (token != NULL)
                arr[len++] = atoi(token);
        }

        count++;
        printf("Input array %d:\t", count);
        printArray(arr, len);
        printf("\n");
        radixSort(arr, len);
        printf("Sorted array %d:\t", count);
        printArray(arr, len);
        printf("\n");
        printf("\n");
    }

    free(arr);
    fclose(inputFile);
    return 0;
}
