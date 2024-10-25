#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "riscv-matrix.h"

void transpose(float* src, float* dest, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            dest[j * rows + i] = src[i * cols + j];
        }
    }
}

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

void matrix_multiply(   int M, int N, int K,
                    int ldc, int ldb, int lda,
                    float *C, 
                    float *A, 
                    float *B)
  {
  float *B_t = (float *) malloc(N*K*sizeof(float));
  transpose(B, B_t, N, K);
  ldb = K;

  float *C_ptr = C;
  float *A_ptr = A;
  float *B_ptr = B_t;

  int panel_size = 4;

  // Matrix Multiplication
  for (int i = 0; i < M; i += panel_size) {
    for (int j = 0; j < N; j += panel_size) {
      C_ptr = C + j + i*ldc;

      // Reset the accumulator
      asm(MZERO(M2));

      for (int k = 0; k < K; k += panel_size) { 
        A_ptr = A + k + i*lda;
        B_ptr = B_t + k + j*ldb;

        asm(
          "mv t0, %0\n\t"
          "mv t1, %1\n\t"
          MLS(M0, T1, T0)
          "mv t0, %2\n\t"
          "mv t1, %3\n\t"
          MLS(M1, T1, T0)
          MMACF(M2, M0, M1)
          :: "r" (lda * 4), "r" (A_ptr), "r" (ldb * 4), "r" (B_ptr)
          : "t0", "t1", "memory"
        );
      }

      // Store C
      asm(
        "mv t0, %0\n\t"
        "mv t1, %1\n\t"
        MSS(M2, T1, T0)
        :: "r" (ldc * 4), "r" (C_ptr)
        : "t0", "t1", "memory"
      );
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
    matrix_multiply(m, n, k, s, s, s, (float*) &c, (float*) &a, (float*) &b);

    printf("## fmmacc ## \n\n");
    printMatrix((float*) &c, s, s);

    return 0;
}

