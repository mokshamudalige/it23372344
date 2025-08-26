#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_POINTS 10000000  // 10 million points

int main() {
    long long count = 0;
    double x, y;
    double pi;
    double tstart, tstop, tcalc;

    tstart = omp_get_wtime();

    #pragma omp parallel private(x,y) reduction(+:count)
    {
        unsigned int seed = omp_get_thread_num(); // different seed per thread
        #pragma omp for
        for (long long i = 0; i < NUM_POINTS; i++) {
            x = (double)rand_r(&seed) / RAND_MAX;
            y = (double)rand_r(&seed) / RAND_MAX;
            if (x*x + y*y <= 1.0)
                count++;
        }
    }

    pi = (4.0 * count) / NUM_POINTS;

    tstop = omp_get_wtime();
    tcalc = tstop - tstart;

    printf("Estimated Pi = %.10f\n", pi);
    printf("Time taken = %f seconds\n", tcalc);

    return 0;
}
