/*
* El programa matrprimos.c que llena una matriz de 2000 renglones y 2000 columnas con números aleatorios que están
* en el rango de 900000000 hasta el 999999999 posteriormente se recorre la matriz buscando qué números son primos y
* qué números no lo son para que en la posición donde se encuentre un número que no es primo, este sea reemplazado
* por un 0. Posteriormente se ejecuta la función printnonzeroes() que muestra en pantalla todos aquellos números que
* están en la matriz y que no son ceros.
* 
* La parte del programa que recorre la matriz para buscar los números que no son primos se lleva mucho tiempo del CPU
* y no aprovecha los núcleos del CPU que están disponibles.
* 
* Modifica el programa para que utilizando hilos haga la búsqueda y reemplazo de los números que no son primos en la matriz. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>

#define SIZE 4000

#define INICIAL 900000000
#define FINAL 1000000000

int mat[SIZE][SIZE];

void initmat(int mat[][SIZE]);
void printnonzeroes(int mat[SIZE][SIZE]);
int isprime(int n);

int main()
{
	long long start_ts;
	long long stop_ts;
	long long elapsed_time;
	long lElapsedTime;
	struct timeval ts;
	int i,j;

	// Inicializa la matriz con números al azar
	initmat(mat);
	
	gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec; // Tiempo inicial

	// Eliminar de la matriz todos los números que no son primos
	// Esta es la parte que hay que paralelizar
	
	for(i=0;i<SIZE;i++)
		for(j=0;j<SIZE;j++)
			if(!isprime(mat[i][j]))
			   mat[i][j]=0;
	
	// Hasta aquí termina lo que se tiene que hacer en paralelo
	gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec; // Tiempo final
	elapsed_time = stop_ts - start_ts;


	printnonzeroes(mat);
	printf("------------------------------\n");
	printf("TIEMPO TOTAL, %lld segundos\n",elapsed_time);
}

void initmat(int mat[][SIZE])
{
	int i,j;
	
	srand(getpid());
	
	for(i=0;i<SIZE;i++)
		for(j=0;j<SIZE;j++)
			mat[i][j]=INICIAL+rand()%(FINAL-INICIAL);
}

void printnonzeroes(int mat[SIZE][SIZE])
{
	int i,j;
	
	for(i=0;i<SIZE;i++)
		for(j=0;j<SIZE;j++)
			if(mat[i][j]!=0)
				printf("%d\n",mat[i][j]);
}

			   
int isprime(int n)
{
	int d=3;
	int prime=n==2;
	int limit=sqrt(n);
	
	if(n>2 && n%2!=0)
	{
		while(d<=limit && n%d)
			d+=2;
		prime=d>limit;
	}
	return(prime);
}