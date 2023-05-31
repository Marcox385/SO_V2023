#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define TAM 2000

double a[TAM][TAM], b[TAM][TAM], c[TAM][TAM];

int main() {
    long long start_ts, end_ts, elapsed_time;
    long lElapsedTime;
    struct timeval ts;

    int i, j, k;

    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec; // Tiempo inicial

    for (i = 0; i < TAM; i++)
        for (j = 0; j < TAM; j++)
            for (k = 0; k < TAM; k++)
                c[i][j] = c[i][j] + a[i][k] * b[k][j];

    gettimeofday(&ts, NULL);
    end_ts = ts.tv_sec;

    elapsed_time = end_ts - start_ts; // Tiempo final
    printf("----------------------------\n");
    printf("TIEMPO TOTAL, %lld segundos\n", elapsed_time);
}
