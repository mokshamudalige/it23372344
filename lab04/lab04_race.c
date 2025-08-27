// lab04_race.c
#include <stdio.h>
#include <omp.h>

int main() {
    long long N = 100000000;
    double pi = 0.0;
    double t0 = omp_get_wtime();

    #pragma omp parallel for
    for (long long i = 0; i < N; i++) {
        double x = (i + 0.5) / (double)N;
        pi += 4.0 / (1.0 + x*x); // data race: multiple threads update pi
    }

    pi /= (double)N;
    double t1 = omp_get_wtime();
    printf("Pi(racy) = %.12f\n", pi);
    printf("Time taken: %f seconds\n", t1 - t0);
    return 0;
}
