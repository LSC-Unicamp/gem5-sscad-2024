#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "riscv-matrix.h"

void printMatrix(float* matrix, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%.3f ", matrix[i * cols + j]);
    }
    printf("\n");
  }
  printf("\n");
}

void fillMatrixWithRandomValues(float* matrix, int rows, int cols) {
    // Seed the random number generator
    srand(42);

    // Fill the matrix with random values
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i * cols + j] = (float) rand() / RAND_MAX * 100.0f;
        }
    }
}

void fillMatrixSequentially(float* matrix, int rows, int cols) {
    float c = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i * cols + j] = c++;
        }
    }
}

void naive_multiply(int M, int N, int K, int ldc, int ldb, int lda, float *C, float *A, float *B) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            float sum = 0.0f;
            for (int k = 0; k < K; k++) {
                sum = (double) A[i * lda + k] * (double) B[k * ldb + j] + (double) sum;
            }
            C[i * ldc + j] = sum;
        }
    }
}

int main() {
    // Gerar a matriz
    int s = 8;
    float a[s][s], b[s][s], c[s][s], d[s][s];

    // Generate random values
    fillMatrixSequentially((float*) &a, s, s);
    fillMatrixWithRandomValues((float*) &b, s, s);

    // Multiply
    int m = s, n = s, k = s;
    naive_multiply(m, n, k, s, s, s, (float*) &c, (float*) &a, (float*) &b);

    printf("##  naive ##\n\n");
    printMatrix((float*) &c, s, s);

    return 0;
}

