#include <stdio.h>
#include <string.h>
#include <limits.h>

int maxLength = 4;

void visitPermutation(int *arr) {
    int i;
    for (i = 0; i < maxLength; i++)
        printf("%d, ", arr[i]);
    printf("\n");
}

void swap(int *arr, int i, int j) {
    int temp;
    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int main() {
    int O[100];
    int C[100];
    int P[100];
    int i, j, Q, S;

    for (i = 0; i < maxLength; i++) {
        C[i] = 0;
        O[i] = 1;
        P[i] = i  + 1;
    }

    while (1) {
        visitPermutation(P);
        j = maxLength - 1;
        S = 0;
        Q = C[j] + O[j];

//        printf("Q: %d", Q);
        while (Q < 0 || Q == j) {
            if (Q == j) {
                if (j == 1) {
                    return 0;
                } else
                    S = S + 1;
            }
            O[j] = -O[j];
            j = j - 1;
            Q = C[j] + O[j];
        }
        swap(P, j - C[j] + S, j - Q + S);
        C[j] = Q;
    }
}