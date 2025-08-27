#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char **argv) {
    long long N = 10000000LL;
    double x = 1.0;
    if (argc >= 2) N = atoll(argv[1]);
    if (argc >= 3) x = atof(argv[2]);

    double t0 = omp_get_wtime();
    double S = 0.0;

    #pragma omp parallel
    {
        #pragma omp for
        for (long long i = 1; i <= N; ++i) {
            double term = (double)i - (double)i*(double)i + 2.0 * x * (double)(i+1);
            #pragma omp critical
            {
                S += term;
            }
        }
    }

    double t1 = omp_get_wtime();
    printf("Critical: N=%lld x=%f S=%.6e\n", N, x, S);
    printf("Time taken: %f seconds\n", t1 - t0);
    return 0;
}
