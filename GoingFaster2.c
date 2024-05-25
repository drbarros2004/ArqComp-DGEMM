//Going Faster 2: Matrix Multiply in C

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void dgemm(int n, double* A, double* B, double* C) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double cij = 0.0;  
            
            for(int k = 0; k < n; k++) {
                cij += A[i + k * n] * B[k + j * n]; 
            }
            
            C[i + j * n] = cij; 
        }
    }
}

void generate_random_matrix(int n, double* matrix) {
    for (int i = 0; i < n * n; i++) {
        matrix[i] = ((double)rand() / RAND_MAX) * 49.0; 
    }
}

int main() {
    srand(clock()); 

    int n = 3; 

    double *a = (double*)malloc(n * n * sizeof(double));
    double *b = (double*)malloc(n * n * sizeof(double));
    double *c = (double*)malloc(n * n * sizeof(double));

    generate_random_matrix(n, a);
    generate_random_matrix(n, b);

    clock_t start_time = clock(); // start time

    dgemm(n, a, b, c);

    clock_t end_time = clock(); // end time

    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // printf("A:\n");
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; ++j) {
    //         printf("%.2f ", a[i * n + j]);
    //     }
    //     printf("\n");
    // }

    // printf("\nB:\n");
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; ++j) {
    //         printf("%.2f ", b[i * n + j]);
    //     }
    //     printf("\n");
    // }

    // printf("\nC (resultado):\n");
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; ++j) {
    //         printf("%.2f ", c[i * n + j]);
    //     }
    //     printf("\n");
    // }

    printf("\nTempo decorrido na multiplicação de matrizes: %.2f segundos\n", elapsed_time);
    fflush(stdout);

    free(a);
    free(b);
    free(c);

    return 0;
}
