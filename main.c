#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define N 12
#define M 10
#define P 5
#define MAX_THREADS 2

int threadNumber;

int a[N][M];
int b[M][P];
int c[N][P];


void initializeMatrices() {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            a[i][j] = i + j;
        }
    }
    for (i = 0; i < M; i++) {
        for (j = 0; j < P; j++) {
            b[i][j] = j;
        }
    }
}

void givenMatMult () {
    // int rowsOfA = sizeof(a) / sizeof(a[0]);             /* a is nxm -- rows = n */
    // int columnsOfA = sizeof(a[0]) / sizeof(a[0][0]);    /* columnsOfA = rowsOfB = m */
    // int columnsOfB = sizeof(b[0]) / sizeof(b[0][0]);    /* b is mxp -- columns = p */
    int i, j, k;
    for (i = 0; i < N; i++) {
        for (j = 0; j < P; j++) {
            c[i][j] = 0;
            for (k = 0; k < M; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void *multiMultip(void *param) {
    int i, j, k;
    int thNum = threadNumber++;
    for (i = thNum * N/ MAX_THREADS; i < (thNum +1) * N / MAX_THREADS; i++) {
        for (j = 0; j < P; j++) {
            for (k = 0; k < M; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int main(void) {
    int i, j;

    pthread_attr_t attr;
    pthread_t tid[MAX_THREADS];
    pthread_attr_init(&attr);

    initializeMatrices();

    // givenMatMult();

    threadNumber = 0;
    for (i = 0; i < MAX_THREADS; i++) {
        if (pthread_create(&(tid[i]), &attr, multiMultip, NULL)) {
            printf("Failed to create thread %d.\n", i);
        } else {
            printf("Thread %d created successfully.\n", i);
        }
    }

    for (i = 0; i < MAX_THREADS; i++) {
        if (pthread_cancel(tid[i])) {
            printf("Failed to cancel thread %d.\n", i);
        } else {
            printf("Thread %d cancelled successfully.\n", i);
        }
        if (pthread_join(tid[i], NULL)) {
            printf("Failed to join thread %d.\n", i);
        } else {
            printf("Thread %d joined successfully.\n", i);
        }
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < P; j++) {
            printf("%3d ", c[i][j]);
        }
        printf("\n");
    }
    return(0);
}