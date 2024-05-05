#include <stdio.h>

void insertionSort(int A[], int length) {
    for (int j = 1; j <= length - 1; j++) {
        int key = A[j];
        int i = j - 1;
        while (i >= 0 && A[i] > key) {
            A[i + 1] = A[i];
            i = i - 1;
        }
        A[i + 1] = key;
    }
}

int main() {
    int A[] = {5, 8, 12, 1, 3, 2, 9, 4, 7};
    int length = sizeof(A) / sizeof(A[0]);
    insertionSort(A, length);
    printf("Sorted array: ");
    for (int k = 0; k < length; k++) {
        printf("%d ", A[k]);
    }
    printf("\n");
    return 0;
}
