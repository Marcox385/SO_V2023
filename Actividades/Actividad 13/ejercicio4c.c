/*  IS727272 - Actividad 13 - Ejercicio 4C

* Considere un programa concurrente con dos procesos P y Q, definidos a
* continuación. la impresión en pantalla de A, B, C, D y E son sentencias
* arbitrarias atómicas (indivisibles). Supóngase que el programa principal
* ejecuta concurrentemente los procesos P y Q. Comprueba tu solución
* empleando semáforos en Linux.
*
* C. Usando semáforos haga que el proceso P ejecute siempre las
*    sentencias B inmediatamente después que A sin que cualquier
*    sentencia de Q se ejecute intercalada entre ellas. 
*
* Compilar: gcc -o ejercicio4c ejercicio4c.c semaphoresarr.c

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
    semwait(semarr, SYNC);
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
    semsignal(semarr, SYNC);
    exit(0);
}

int main() 
{
    int p;

    // Crear semáforos (Solicitar al OS un arreglo de semáforos)
    semarr = createsemarray(0x4321, 1);
    initsem(semarr, 0, 1); // Inicializar semáforo 0 con valor de 1

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
