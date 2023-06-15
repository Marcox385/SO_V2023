/*  IS727272 - Actividad 13 - Ejercicio 4B

* Considere un programa concurrente con dos procesos P y Q, definidos a
* continuación. la impresión en pantalla de A, B, C, D y E son sentencias
* arbitrarias atómicas (indivisibles). Supóngase que el programa principal
* ejecuta concurrentemente los procesos P y Q. Comprueba tu solución
* empleando semáforos en Linux.
*
* B. Usando semáforos sincronice P y Q de manera que se asegure que las
*    sentencias A y B se ejecutan antes que D.
*
* Compilar: gcc -o ejercicio4b ejercicio4b.c semaphoresarr.c

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "semaphoresarr.h"

int semarr;
#define SYNC 0

void imprime(char *s)
{
    usleep(rand()%100000);
    printf("%s\n",s);
    usleep(rand()%100000);
}

void P()
{
    imprime("A");
    imprime("B");
    semsignal(semarr, SYNC);
    imprime("C");
    exit(0);
}

void Q()
{
    semwait(semarr, SYNC);
    imprime("D");
    imprime("E");
    exit(0);
}

int main() 
{
    int p;

    // Crear semáforos (Solicitar al OS un arreglo de semáforos)
    semarr = createsemarray(0x4321, 1);
    initsem(semarr, 0, 0); // Inicializar semáforo 0 con valor de 0

    srand(getpid());

    p=fork();
    if(p==0)
        P();

    p=fork();
    if(p==0)
        Q();

    wait(NULL);
    wait(NULL);

    erasesem(semarr);
}
