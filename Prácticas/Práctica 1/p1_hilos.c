/*
    Cálculo de PI a través de regla del trapecio - Versión Multithreaded

    Equipo 3
    IS727223 - Paez Aguilar, Carlos Andrés
    IS727272 - Cordero Hernández, Marco Ricardo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>

// Para imprimir cambio de resultado en tiempo real
#define SHOW_OUTPUT 0

// Total de cores disponibles en el sistema
#define NTHREADS sysconf(_SC_NPROCESSORS_ONLN)

int ITERS; // Contenedor de cantidad de iteraciones
double factor; // Variable para establecer cantidad de rectángulos
double g_sum = 0.0; // Acumulador para resultado
pthread_mutex_t mutex; // Auxiliar para control de threads

// Función matemática para cuarto de la circunferencia
double f(double x) {
    return sqrt(1 - pow(x, 2));
}

// Función auxiliar para manejo de threads
void *tfunc(void *args) {
	int tnum = *((int *)args); // ID del thread
	int inicio = (tnum == 0) ? 1 : tnum * (ITERS/NTHREADS); // Inicio de sección del cálculo (inclusivo)
    int fin = inicio + (ITERS/NTHREADS); // Fin de sección del cálculo (excluyente)
	double local = 0.0; // Suma local (relacionado a segmentos de memoria compartida)
    int n; // Auxiliar para iterador

	// Aumentar acumulador con el área de los rectángulos
	for(n = inicio; n < fin; n++)
		local += factor * f(((2*n + 1.0)/ITERS)/2);

	// Solicitar acceso a memoria para actualizar el resultado actual y luego liberarla
	pthread_mutex_lock(&mutex);
	g_sum += local;
	pthread_mutex_unlock(&mutex);
}

int main() {
    // Variables relacionadas a threads
	pthread_t tid[NTHREADS]; // Arreglo de threads
	int targs[NTHREADS]; // Identificadores de threads

    int i; // Auxiliar para iterador
	int PI_FACTOR = 4; // Constante de multiplicación

	/* Segmento de variables para temporizador */
    long long start_ts;
	long long stop_ts;
	long long elapsed_time;
	long lElapsedTime;
	struct timeval ts;
	/* --------------------------------------- */

	// Obtención de cantidad de iteraciones
    while (1) {
        printf("Ingresa el número de iteraciones (mayor a 0, menor que 1e10): ");
	    scanf("%d", &ITERS);

        if (ITERS > 0 && ITERS < 10000000000) // Rango de (0, 10000000000)
            break;
        
        printf("\33[2K\r\nValor de entrada incorrecto. Intenta de nuevo.\n");
    } 

    factor = 1.0/ITERS; // Guardado de separación de rectángulos

	// Iniciar temporizador
    gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec;

    // Inicia segmento de paralelización
	pthread_mutex_init(&mutex, NULL); // Inicialización de controlador de threads

	// Creación de threads
	for (i = 0; i < NTHREADS; i++) {
		targs[i] = i; // Guardado de identificador de thread
		pthread_create(&tid[i], NULL, tfunc, &targs[i]);
	}

	// Conjunción de threads
	for (i = 0; i < NTHREADS; i++)
		pthread_join(tid[i], NULL);

	pthread_mutex_destroy(&mutex); // Finalizar controlador de threads
	//  Termina segmento de paralelización

	// Multiplicar por 4 para obtener el resultado esperado
    g_sum *= PI_FACTOR;

	// Detener temporizador
    gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec; // Tiempo final

	elapsed_time = stop_ts - start_ts;
	printf("\33[2K\rResultado = %.30lf\n", g_sum);
	printf("------------------------------\n");
	printf("TIEMPO TOTAL, %lld segundos\n", elapsed_time);
}
