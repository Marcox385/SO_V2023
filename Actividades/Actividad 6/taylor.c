/*
El progarama taylor.c es un programa que a través de una serie calcula el logaritmo natural
de n+1. Para calcular un valor preciso se hacen 1000 millones de itreraciones lo que se lleva
un tiempo considerable del CPU. 

Modifica el programa para que utilizando hilos, este cálculo se realice en menos tiempo utilizando
los núcleos del CPU

Tomar en cuenta condiciones de concurso y considerar mutex
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>

#define ITERS 1000000000

int main()
{
	long long start_ts;
	long long stop_ts;
	long long elapsed_time;
	long lElapsedTime;
	struct timeval ts;
	int n;
	double sum = 0.0;
	float x;

	printf("Calcular el logaritmo natural de 1+x\n");
	printf("Dame el valor de x :");
	scanf("%f",&x);
	
	gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec; // Tiempo inicial

	for(n=1;n<ITERS;n++)
		sum = sum + pow(-1,n+1) * pow(x,n) / n;
	
	gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec; // Tiempo final

	elapsed_time = stop_ts - start_ts;
	printf("Resultado = %.4lf\n",sum);
	printf("------------------------------\n");
	printf("TIEMPO TOTAL, %lld segundos\n",elapsed_time);
}
