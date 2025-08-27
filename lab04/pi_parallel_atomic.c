#include <stdio.h>
#include <omp.h>

#define N 10000000

int main() {
    double pi = 0.0;
    double tstart, tstop, tcalc;

    tstart = omp_get_wtime();

    #pragma omp parallel
    {
        double sum = 0.0;
        #pragma omp for
        for (int i = 1; i <= N; i++) {
            double x = (i - 0.5)/N;
            sum += 1.0 / (1.0 + x*x);
        }
        #pragma omp atomic
        pi += sum;
    }

    pi = pi / N * 4;

    tstop = omp_get_wtime();
    tcalc = tstop - tstart;

    printf("Calculated Pi = %.12f\n", pi);
    printf("Time taken = %f seconds\n", tcalc);

    return 0;
}
