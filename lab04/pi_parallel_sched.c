#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#ifndef N
#define N 10000000   /* default 10 million; change if you want */
#endif

int main(int argc, char **argv) {
    long long N_local = N;
    if (argc > 1) N_local = atoll(argv[1]);

    double pi = 0.0;
    double tstart, tstop;

    /* demonstrate firstprivate, private, shared usage */
    int base = 42;      /* will be firstprivate */
    int tid;            /* will be private */
    double local_sum;   /* will be private */

    tstart = omp_get_wtime();

    #pragma omp parallel shared(pi) firstprivate(base) private(tid, local_sum)
    {
        tid = omp_get_thread_num();
        local_sum = 0.0;

        /* schedule(runtime) allows us to set OMP_SCHEDULE externally */
        #pragma omp for schedule(runtime)
        for (long long i = 1; i <= N_local; ++i) {
            double x = (i - 0.5) / (double)N_local;
            local_sum += 1.0 / (1.0 + x*x);
        }

        /* atomic to safely add the local_sum into shared pi */
        #pragma omp atomic
        pi += local_sum;
    }

    tstop = omp_get_wtime();

    pi = pi / (double)N_local * 4.0;
    printf("Calculated Pi = %.12f\n", pi);
    printf("Time taken = %f seconds\n", tstop - tstart);
    return 0;
}
