#include <stdio.h>

int main() {
    long long N = 100000000; // 100 million iterations
    double pi = 0.0;

    for (long long i = 0; i < N; i++) {
        double x = (i + 0.5) / N;
        pi += 4.0 / (1.0 + x * x);
    }

    pi /= N;

    printf("Calculated Pi = %.12f\n", pi);

    return 0;
}
