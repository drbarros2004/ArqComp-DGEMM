#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>

#define UNROLL (4)
#define BLOCKSIZE 32

void print_matrix(size_t n, double* A) {
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            printf("%8.2lf ", A[(i * n) + j]);
        }
        printf("\n");
    }
    printf("\n");
}

void do_block(int n, int si, int sj, int sk, double* A, double* B, double* C) {
    for (int i = si; i < si + BLOCKSIZE; i++) {
        for (int j = sj; j < sj + BLOCKSIZE; j += 4 * UNROLL) {
            __m256d c[UNROLL];
            for (int r = 0; r < UNROLL; r++)
                c[r] = _mm256_load_pd(C + (i * n) + j + r * 4);

            for (int k = sk; k < sk + BLOCKSIZE; k++) {
                __m256d bb = _mm256_broadcast_sd(A + (i * n) + k);
                for (int r = 0; r < UNROLL; r++)
                    c[r] = _mm256_add_pd(c[r], _mm256_mul_pd(bb, _mm256_load_pd(B + (n * k) + j + 4 * r)));
            }

            for (int r = 0; r < UNROLL; r++)
                _mm256_store_pd(C + (i * n) + j + r * 4, c[r]);
        }
    }
}

void dgemm(int n, double* A, double* B, double* C) {
    #pragma omp parallel for
    for (int si = 0; si < n; si += BLOCKSIZE) {
        for (int sj = 0; sj < n; sj += BLOCKSIZE) {
            for (int sk = 0; sk < n; sk += BLOCKSIZE) {
                do_block(n, si, sj, sk, A, B, C);
            }
        }
    }
}

void make_rand_matrix(size_t n, double* A, int offset) {
    srand(clock() + offset);
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            A[i * n + j] = (double)rand() / RAND_MAX * 49.0;
        }
    }
}

int main() {
    size_t n = 8192;

    double* A = (double*)malloc(n * n * sizeof(double));
    double* B = (double*)malloc(n * n * sizeof(double));
    double* C = (double*)malloc(n * n * sizeof(double));

    if (A == NULL || B == NULL || C == NULL) {
        fprintf(stderr, "Erro na alocação de memória\n");
        return 1;
    }

    make_rand_matrix(n, A, 0);
    make_rand_matrix(n, B, 3);

    clock_t start_time = clock();

    dgemm(n, A, B, C);

    clock_t end_time = clock();

    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // printf("A:\n");
    // print_matrix(n, A);
    // printf("B:\n");
    // print_matrix(n, B);
    // printf("C (resultado):\n");
    // print_matrix(n, C);

    printf("\nTempo decorrido na multiplicação de matrizes: %.2f segundos\n", elapsed_time);
    fflush(stdout);

    free(A);
    free(B);
    free(C);

    return 0;
}

//gcc -O3 -mavx2 dgemm5.c
// ./a.exe