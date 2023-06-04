#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>

#define SHOW_OUTPUT 0

double f(double x) {
    return sqrt(1 - pow(x, 2));
}

int main() {
    double acc = 0;
    int i, ITERS, PI_FACTOR = 4;

    long long start_ts;
	long long stop_ts;
	long long elapsed_time;
	long lElapsedTime;
	struct timeval ts;

    while (1) {
        printf("Ingresa el número de iteraciones (mayor a 0, menor que 1e10): ");
	    scanf("%d", &ITERS);

        if (ITERS > 0 && ITERS < 10000000000)
            break;
        
        printf("\33[2K\r\nValor de entrada incorrecto. Intenta de nuevo.\n");
    } 

    double factor = 1.0/ITERS;

    gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec; // Tiempo inicial

    for (i = 0; i < ITERS; i++) {
        if (SHOW_OUTPUT && (ITERS < 10000 || ITERS % 500 == 0))
            printf("\33[2K\rResultado = %.30lf", acc * PI_FACTOR);

        acc += factor * f(((2*i + 1.0)/ITERS)/2);
    }

    acc *= PI_FACTOR;

    gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec; // Tiempo final

	elapsed_time = stop_ts - start_ts;
	printf("\33[2K\rResultado = %.30lf\n", acc);
	printf("------------------------------\n");
	printf("TIEMPO TOTAL, %lld segundos\n", elapsed_time);
}
