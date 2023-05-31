#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>

#define NTHREADS 8

#define ITERS 1000000000

float x;
double g_sum = 0.0;
pthread_mutex_t mutex;

void *tfunc(void *args) {
	int tnum = *((int *)args);
	int inicio = (tnum == 0) ? 1 : tnum * (ITERS/NTHREADS);
    int fin = inicio + (ITERS/NTHREADS);
	double local = 0;
    int n;

	for(n=inicio;n<fin;n++) {
		local += pow(-1,n+1) * pow(x,n) / n;
	}

	pthread_mutex_lock(&mutex);
	g_sum += local;
	pthread_mutex_unlock(&mutex);
}

int main()
{
	// Variables relacionadas a threads
	pthread_t tid[NTHREADS];
	int targs[NTHREADS];

	long long start_ts;
	long long stop_ts;
	long long elapsed_time;
	long lElapsedTime;
	struct timeval ts;
	int n, i;

	printf("Calcular el logaritmo natural de 1+x\n");
	printf("Dame el valor de x :");
	scanf("%f",&x);
	
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
	
	gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec; // Tiempo final

	elapsed_time = stop_ts - start_ts;
	printf("Resultado = %.4lf\n", g_sum);
	printf("------------------------------\n");
	printf("TIEMPO TOTAL, %lld segundos\n",elapsed_time);
}
