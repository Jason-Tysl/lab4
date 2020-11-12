#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define N 1200
#define M 1000
#define P 500
#define MAX_THREADS 7

int threadNumber, threads;

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
    for (i = thNum * N/ threads; i < (thNum +1) * N / threads; i++) {
        for (j = 0; j < P; j++) {
            for (k = 0; k < M; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

int main(void) {
    int i;

    struct timeval startTime, endTime;
    pthread_attr_t attr;
    pthread_t tid[MAX_THREADS];
    pthread_attr_init(&attr);

    initializeMatrices();

    gettimeofday(&startTime, NULL);
    givenMatMult();
    gettimeofday(&endTime, NULL);
    printf("Time for one: %ld microseconds\n", endTime.tv_usec - startTime.tv_usec);
    printf("Threads\tSeconds\tError\n");
    for (threads = 0; threads < MAX_THREADS; threads++) {
        printf("%d\t", threads + 1);
        gettimeofday(&startTime, NULL);
        threadNumber = 0;
        char *errorString = "No error\n";
        for (i = 0; i < threads; i++) {
            if (pthread_create(&(tid[i]), &attr, multiMultip, NULL)) {
                errorString = "Error\n";
            }
        }

        for (i = 0; i < threads; i++) {
            if (pthread_join(tid[i], NULL)) {
                errorString = "Error\n";
            }
        }
        gettimeofday(&endTime, NULL);
        printf("%f\t%s", endTime.tv_sec - startTime.tv_sec + (endTime.tv_usec - startTime.tv_usec)/1000000.0, errorString);
    }
    

    return(0);
}