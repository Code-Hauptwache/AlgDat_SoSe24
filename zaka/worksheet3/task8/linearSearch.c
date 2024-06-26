#include <stdio.h>
#include <stdlib.h>

int lsearch(int k, int a[], int size);

int main()
{
    int result;
    int arr[] = {1, 3, 4, 5, 8, 9, 10, 12, 14, 16, 20};
    int key = 10;
    int arrLen = sizeof(arr) / sizeof(arr[0]);

    result = lsearch(key, arr, arrLen);

    if (result == -1)
        printf("Element not found\n");
    else
        printf("Element found at index %d\n", result);

    return 0;
}

int lsearch(int k, int a[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (k == a[i])
            return i;
    }

    return -1;
}