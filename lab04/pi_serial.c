// pi_serial.c
#include <stdio.h>

int main() {
    long long N = 100000000; // adjust if too slow (100M)
    double pi = 0.0;
    for (long long i = 0; i < N; i++) {
        double x = (i + 0.5) / (double)N;
        pi += 4.0 / (1.0 + x * x);
    }
    pi /= (double)N;
    printf("Pi(serial) = %.12f\n", pi);
    return 0;
}
