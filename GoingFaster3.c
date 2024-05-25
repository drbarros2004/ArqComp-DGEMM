#Going Faster 3

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <x86intrin.h>

void dgemm(size_t n, double* a, double* b, double* c){ 

  for (size_t i = 0; i < n; i+=4) {
    for (size_t j = 0; j < n; j++) {

      __m256d c0 = _mm256_load_pd(c + i + (j*n));

      for (size_t k = 0; k < n; k++) {

        c0 = _mm256_add_pd(c0, _mm256_mul_pd(_mm256_broadcast_sd(a + i + (k*n)), _mm256_load_pd(b+ k + (j*n))));

      }

      _mm256_store_pd(c + i + (j*n), c0); 

    }
  }
}


void generate_random_matrix(size_t n, double* matrix) {

  for (size_t i = 0; i < n * n; i++) {
    matrix[i] = ((double)rand() / RAND_MAX) * 49.0;
  }
}

int main() {

  size_t n = 2048;

  double *a = (double*)malloc(n * n * sizeof(double));
  double *b = (double*)malloc(n * n * sizeof(double));
  double *c = (double*)malloc(n * n * sizeof(double));


  srand((unsigned int)time(NULL)); 
  generate_random_matrix(n, (double * ) a);

  srand((unsigned int)time(NULL) + 27); 
  generate_random_matrix(n, (double * ) b);

  clock_t start_time = clock(); 

  dgemm(n, (double *)a, (double *)b, (double *)c);

  clock_t end_time = clock(); 

  double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

  printf("A:\n");
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < n; j++) {
        printf("%8.2lf ", a[(i * n) + j]);
      }
      printf("\n");
    }

  printf("\nB:\n");
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < n; j++) {
        printf("%8.2lf ", b[(i * n) + j]);
      }
      printf("\n");
    }

  printf("\nC (resultado):\n");
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < n; j++) {
        printf("%8.2lf ", c[(i * n) + j]);
      }
      printf("\n");
  }

 printf("\nTempo decorrido na multiplicação de matrizes: %.2f segundos\n", elapsed_time);
 fflush(stdout);

 free(a);
 free(b);
 free(c);

 return 0;
}
