#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define n 12
#define m 10
#define p 5

void initializeMatrices(int a[n][m], int b[m][p]) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            a[i][j] = i + j;
        }
    }
    for (i = 0; i < m; i++) {
        for (j = 0; j < p; j++) {
            b[i][j] = j;
        }
    }
}

void givenMatMult (int a[n][m], int b[m][p], int c[n][p]) {
    // int rowsOfA = sizeof(a) / sizeof(a[0]);             /* a is nxm -- rows = n */
    // int columnsOfA = sizeof(a[0]) / sizeof(a[0][0]);    /* columnsOfA = rowsOfB = m */
    // int columnsOfB = sizeof(b[0]) / sizeof(b[0][0]);    /* b is mxp -- columns = p */
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < p; j++) {
            c[i][j] = 0;
            for (k = 0; k < m; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int main(void) {
    int a[n][m];
    int b[m][p];
    int c[n][p];
    int i, j;
    initializeMatrices(a, b);
    
    givenMatMult(a, b, c);

    for (i = 0; i < n; i++) {
        for (j = 0; j < p; j++) {
            printf("%3d ", c[i][j]);
        }
        printf("\n");
    }
}