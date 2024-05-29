#include <stdio.h>

int triple_sum_incrementer(int A[], int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        sum += A[i];
    }
    return (length + 2) * sum + 3;
}

int main() {
    int A[] = {1, 2, 3, 4, 5};
    int length = sizeof(A) / sizeof(A[0]);
    int result = triple_sum_incrementer(A, length);
    printf("Result: %d\n", result);
    return 0;
}
