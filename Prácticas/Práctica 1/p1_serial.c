/*
    Práctica 1
    Cálculo de PI a través de regla del trapecio - Versión Serial

    Equipo 3
    IS727223 - Paez Aguilar, Carlos Andrés
    IS727272 - Cordero Hernández, Marco Ricardo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>

// Para imprimir cambio de resultado en tiempo real
#define SHOW_OUTPUT 0

// Función matemática para cuarto de la circunferencia
double f(double x) {
    return sqrt(1 - pow(x, 2));
}

int main() {
    double acc = 0; // Acumulador para resultado
    int i; // Auxiliar para iterador
    int ITERS; // Contenedor de cantidad de iteraciones
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

    double factor = 1.0/ITERS; 

    // Iniciar temporizador
    gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec;

    for (i = 0; i < ITERS; i++) {
        /* Mostrar cambio de resultado en tiempo real si
        si la salidad está activada y las iteraciones son pocas */
        if (SHOW_OUTPUT && (ITERS < 10000 || ITERS % 500 == 0))
            printf("\33[2K\rResultado = %.30lf", acc * PI_FACTOR);

        // Aumentar acumulador con el área de los rectángulos
        acc += factor * f(((2*i + 1.0)/ITERS)/2);
    }

    // Multiplicar por 4 para obtener el resultado esperado
    acc *= PI_FACTOR;

    // Detener temporizador
    gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec;

	elapsed_time = stop_ts - start_ts; // Tiempo total
	printf("\33[2K\rResultado = %.30lf\n", acc);
	printf("------------------------------\n");
	printf("TIEMPO TOTAL, %lld segundos\n", elapsed_time);
}
