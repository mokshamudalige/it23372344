#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 10000

int main() {
    double *A = (double *)malloc(SIZE * sizeof(double));
    double *B = (double *)malloc(SIZE * sizeof(double));
    double *C = (double *)malloc(SIZE * sizeof(double));

    // Initialize arrays
    for (int i = 0; i < SIZE; i++) {
        A[i] = i * 0.5;
        B[i] = i * 2.0;
    }

    // Set number of threads explicitly
    int num_threads = 4;
    omp_set_num_threads(num_threads);
    printf("Running with %d threads.\n", num_threads);

    double start_time = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        C[i] = A[i] + B[i];
    }

    double end_time = omp_get_wtime();

    printf("Completed computation. Sample result: C[100] = %f\n", C[100]);
    printf("Time taken: %f seconds\n", end_time - start_time);

    free(A);
    free(B);
    free(C);

    return 0;
}
