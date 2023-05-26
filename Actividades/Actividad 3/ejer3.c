/*
*3.- Desarrolla un programa que reciba como argumento desde la línea de comandos un valor
* de entrada n cuyo significado sera un número de procesos a crear, de manera que cuando
* ejecutes tu programa este será el proceso padre que creará solamente n procesos hijos a
* un nivel, cada proceso hijo mostrará su número que será de 1 hasta n. El proceso padre
* deberá esperar a que  todos los hijos terminen para al finalizar mostrar en pantalla el
* mensaje "Fin". Por ejemplo:
*
*   $ ./programa 5
*   Proceso hijo 1
*   Proceso hijo 2
*   Proceso hijo 3
*   Proceso hijo 4
*   Proceso hijo 5
*   Fin
*
*   No te preocupes si las salidas en pantalla no están en orden.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int i;

int main(int argc, char *argv[]) {
    int cantidad = atoi(argv[1]), p;

    for (i = 0; i < cantidad; i++) {
        p = fork();
        if (p == 0) {
            printf("Proceso hijo %d\n", i + 1);
            exit(0);
        }
        wait(NULL);
    }

    wait(NULL);
    printf("Fin\n");
}
