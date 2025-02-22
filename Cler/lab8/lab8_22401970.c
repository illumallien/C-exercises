#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mergeSort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);
void mergeSortWrapper(int arr[], int n);
void selectionSort(int arr[], int n);
void insertionSort(int arr[], int n);
void generateRandomArray(int arr[], int n);
void printAverageTime(void (*sortFunc)(int[], int), int arr[], int size, const char *sortName);

int main()
{
    int size1 = 1000;
    int size2 = 10000;
    int *arr1 = (int *)malloc(size1 * sizeof(int));
    int *arr2 = (int *)malloc(size2 * sizeof(int));

    if (!arr1 || !arr2)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    printAverageTime(mergeSortWrapper, arr1, size1, "Merge Sort with 1K elements");
    printAverageTime(mergeSortWrapper, arr2, size2, "Merge Sort with 10K elements");

    printAverageTime(selectionSort, arr1, size1, "Selection Sort with 1K elements");
    printAverageTime(selectionSort, arr2, size2, "Selection Sort with 10K elements");

    printAverageTime(insertionSort, arr1, size1, "Insertion Sort with 1K elements");
    printAverageTime(insertionSort, arr2, size2, "Insertion Sort with 10K elements");

    free(arr1);
    free(arr2);
    return 0;
}

void mergeSortWrapper(int arr[], int n)
{
    mergeSort(arr, 0, n - 1);
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void selectionSort(int arr[], int n)
{
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void generateRandomArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 10000;
    }
}

void printAverageTime(void (*sortFunc)(int[], int), int arr[], int size, const char *sortName)
{
    double totalTime = 0;
    for (int i = 0; i < 5; i++)
    {
        generateRandomArray(arr, size);
        clock_t start = clock();
        sortFunc(arr, size);
        clock_t end = clock();
        totalTime += (double)(end - start) / CLOCKS_PER_SEC;
    }
    printf("%s: Average time = %lf seconds\n", sortName, totalTime / 5);
}
