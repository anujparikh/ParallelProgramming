#include <stdio.h>
#include <pthread.h>

int inputMatrix1[128][128];
int inputMatrix2[128][128];
int finalOutputMatrix[128][128];

void *matrix_add(void *input) {
    int treadId = *(int *) input;
    int i, j;

    for (i = (treadId * 16); i < (treadId * 16) + 16; i++) {
        for (j = 0; j < 128; j++) {
            finalOutputMatrix[i][j] = inputMatrix1[i][j] + inputMatrix2[i][j];
        }
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t thread[8];
    int tid[8];
    int i, j;
    FILE *outputFile;
    outputFile = fopen("output.txt", "w+");
    for (i = 0; i < 128; i++) {
        for (j = 0; j < 128; j++) {
            inputMatrix1[i][j] = j + 1;
            inputMatrix2[i][j] = j + 1;
        }
    }

    for (i = 0; i < 8; i++) {
        tid[i] = i;
        pthread_create(&thread[i], NULL, matrix_add, &tid[i]);
    }

    for (i = 7; i >= 0; i--) {
        pthread_join(thread[i], NULL);
        printf("Thread %d: Done\n", i + 1);
    }

    for (i = 0; i < 128; i++) {
        for (j = 0; j < 128; j++) {
            printf((j < 127) ? "%d " : "%d\n", finalOutputMatrix[i][j]);
            fprintf(outputFile, (j < 127) ? "%d " : "%d\n", finalOutputMatrix[i][j]);
        }
    }
}