#include <stdio.h>
#include <omp.h>

int main() {
    long long N = 100000000;
    double pi = 0.0;

    double tstart = omp_get_wtime();

    #pragma omp parallel for reduction(+:pi)
    for (long long i = 0; i < N; i++) {
        double x = (i + 0.5) / N;
        pi += 4.0 / (1.0 + x * x);
    }

    pi /= N;

    double tstop = omp_get_wtime();
    double tcalc = tstop - tstart;

    printf("Calculated Pi = %.12f\n", pi);
    printf("Time taken = %f seconds\n", tcalc);

    return 0;
}
