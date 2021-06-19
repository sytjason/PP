#include "matrix.h"
 
void swap(unsigned long *x, unsigned long *y) {
    unsigned long tmp = *x;
    *x = *y;
    *y = tmp;
}

void fastMultiply(int N, unsigned long A[][2048], unsigned long B[][2048], unsigned long C[][2048]) {
#pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = N-1; j > i; j--) {
            swap(&B[i][j], &B[j][i]);
        }
    }

#pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            unsigned long sum = 0;    // overflow, let it go.
            for (int k = 0; k < N; k++)
                sum += A[i][k] * B[j][k];
            C[i][j] = sum;
        }
    }
}