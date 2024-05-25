// Going Faster 4: Instruction-Level Parallelism (ILP)

#include <x86intrin.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#define UNROLL (4)

void print_matrix(size_t n, double* A){
  for (size_t i = 0; i < n; i++){   
    for (size_t j = 0; j < n; j++){
      printf("%8.2lf ", A[(i * n) + j]);
    }
    printf("\n");
  }
  printf("\n");
}

void dgemm(size_t n, double* A, double* B, double* C){ // A * B^T = C^T
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j += 4 * UNROLL){
            __m256d c[UNROLL];
            for (int r = 0; r < UNROLL; r++)
                c[r] = _mm256_load_pd(C + (i * n) + j + r * 4);

            for (size_t k = 0; k < n; k++){
                __m256d bb = _mm256_broadcast_sd(A + (i * n) + k);
                for (int r = 0; r < UNROLL; r++){
                    c[r] = _mm256_add_pd(c[r], _mm256_mul_pd(bb, _mm256_load_pd(B + (n * k) + j + 4 * r)));
                }
            }
            for (int r = 0; r < UNROLL; r++)
                _mm256_store_pd(C + (i * n) + j + r * 4, c[r]);
        }
}

void make_rand_matrix(size_t n, double* A, int offset) {
    srand(clock() + offset); // Adiciona um deslocamento fixo à semente de aleatoriedade
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            A[i * n + j] = (double)rand() / RAND_MAX * 49.0;
        }
    }
}

int main(){
  
    size_t n = 1024;
    // printf("Insira o valor de n: ");
    // scanf("%zu", &n);

    double *A = (double*)malloc(n * n * sizeof(double));
    double *B = (double*)malloc(n * n * sizeof(double));
    double *C = (double*)malloc(n * n * sizeof(double));

    if (A == NULL || B == NULL || C == NULL) {
        fprintf(stderr, "Erro na alocação de memória\n");
        return 1;
    }

    make_rand_matrix(n, A, 0);
    make_rand_matrix(n, B, 3); // Offset de 1 para garantir valores diferentes para B

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

// gcc -O3 -mavx2 -o DGEMM_4 DGEMM_4.c 
// ./DGEMM_4.exe

// 1024, 2048, 4096, 8192
