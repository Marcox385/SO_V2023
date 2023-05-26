/*
* 2.- Desarrolla un programa que reciba como argumento desde la línea de comandos un valor
* de entrada n cuyo significado sera nivel. Ese nivel tendrá el significado de cuántos niveles
* tendrá un árbol de procesos y al finalizar deberá haber 2n procesos donde cada proceso deberá
* ir mostrando en pantalla  un número que será el nivel en el que se encuentre actualmente,
* de manera que cada uno de los procesos estará mostrando en pantalla todos los niveles por
* los que va pasando. Por ejemplo:
*
*    Si n=1 terminarán dos procesos que deberán mostrar en pantalla 0,1,1
*    Si n=2 terminarán cuatro procesos que deberán mostrar en pantalla 0,1,1,2,2,2,2
*    Si n=4 terminarán 16 procesos que deberán mostrar en pantalla 0,1,1,2,2,2,2,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
*
* No es necesario que los números que se van mostrando en pantalla se muestren en orden.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int i;

int main(int argc, char *argv[]) { // FALTA CORREGIR
    int nivel = atoi(argv[1]), counter = 0, p;

    printf("%d", counter);

    for (i = 0; i < nivel; i++) {
        p = fork();
        counter++;

        if (p == 0) printf(",%d", counter);
    }

    wait(NULL);
    printf("\n");
}
