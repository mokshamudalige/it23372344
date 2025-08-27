#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main() {
    long N = 10000000; // 10 million
    long count = 0;
    double x, y;

    double tstart = omp_get_wtime();

    #pragma omp parallel
    {
        unsigned int seed = omp_get_thread_num() + time(NULL); // thread-local seed
        #pragma omp for
        for (long i = 0; i < N; i++) {
            x = (double)rand_r(&seed)/RAND_MAX;
            y = (double)rand_r(&seed)/RAND_MAX;
            if (x*x + y*y <= 1.0) {
                #pragma omp atomic
                count++;  // atomic fixes data race
            }
        }
    }

    double pi = 4.0 * count / N;

    double tstop = omp_get_wtime();
    double tcalc = tstop - tstart;

    printf("Calculated Pi = %.12f\n", pi);
    printf("Time taken = %f seconds\n", tcalc);

    return 0;
}
