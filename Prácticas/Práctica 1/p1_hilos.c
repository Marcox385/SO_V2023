#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>

#define SHOW_OUTPUT 0
#define NTHREADS sysconf(_SC_NPROCESSORS_ONLN)

int ITERS;
double factor, g_sum = 0.0;
pthread_mutex_t mutex;

double f(double x) {
    return sqrt(1 - pow(x, 2));
}

void *tfunc(void *args) {
	int tnum = *((int *)args);
	int inicio = (tnum == 0) ? 1 : tnum * (ITERS/NTHREADS);
    int fin = inicio + (ITERS/NTHREADS);
	double local = 0.0;
    int n;

	for(n = inicio; n < fin; n++) {
		local += factor * f(((2*n + 1.0)/ITERS)/2);
	}

	pthread_mutex_lock(&mutex);
	g_sum += local;
	pthread_mutex_unlock(&mutex);
}

int main() {
    // Variables relacionadas a threads
	pthread_t tid[NTHREADS];
	int targs[NTHREADS];

    int i, PI_FACTOR = 4;

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

    factor = 1.0/ITERS;

    gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec; // Tiempo inicial

    // Inicia segmento de paralelización
	pthread_mutex_init(&mutex, NULL);

	for (i = 0; i < NTHREADS; i++) {
		targs[i] = i;
		pthread_create(&tid[i], NULL, tfunc, &targs[i]);
	}

	for (i = 0; i < NTHREADS; i++)
		pthread_join(tid[i], NULL);

	pthread_mutex_destroy(&mutex);
	//  Termina segmento de paralelización

    g_sum *= PI_FACTOR;

    gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec; // Tiempo final

	elapsed_time = stop_ts - start_ts;
	printf("\33[2K\rResultado = %.30lf\n", g_sum);
	printf("------------------------------\n");
	printf("TIEMPO TOTAL, %lld segundos\n", elapsed_time);
}
