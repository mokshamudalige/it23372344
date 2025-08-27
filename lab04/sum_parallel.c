#include <stdio.h>
#include <omp.h>

int main() {
    long long N = 10000000;
    double sum = 0.0;
    double tstart, tstop, tcalc;

    tstart = omp_get_wtime();

    #pragma omp parallel for
    for(long long i = 1; i <= N; i++) {
        double temp = i - (i*i) + 2.0*(i+1);
        #pragma omp critical
        sum += temp;
    }

    tstop = omp_get_wtime();
    tcalc = tstop - tstart;

    printf("Sum = %lf\n", sum);
    printf("Time taken: %lf seconds\n", tcalc);

    return 0;
}
