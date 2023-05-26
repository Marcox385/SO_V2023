/*
* 1.- Escribir un programa que cree un hijo. El hijo debe escribir: "Soy el hijo"
* diez veces. El padre debe escribir: "Soy el padre" diez veces. Ambos procesos deberán
* mostrar concurrentemente sus líneas en pantalla y entre cada linea que escriban deben
* hacer una pausa de un segundo. El padre debe esperar a que termine el hijo y mostrar el
* mensaje: "Mi proceso hijo ya ha terminado".
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int i;

int main() {
    int p, retval;

    p = fork();

    if (p == 0) { // Hijo
        for (i = 0; i < 10; i++) {
            printf("Soy el hijo\n");
            sleep(1);
        }

        exit(0);
    }

    for (i = 0; i < 10; i++) { // Padre
        printf("Soy el padre\n");
        sleep(1);
    }

    p = wait(&retval);
    printf("Mi proceso hijo ya ha terminado\n");
}
