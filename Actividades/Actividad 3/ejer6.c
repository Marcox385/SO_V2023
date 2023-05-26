/*
* 6.- Repite el ejercicio anterior, pero ahora una vez introducido el nombre del programa,
* no deberá esperar a que este termine, si no deberá permitir que se introduzca el nombre
* de otro programa que también se lanzará a ejecución, es decir, los programas se ejecutarán
* en segundo plano.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() { // NOTA: NO FUNCIONA
    int p, retval;
    char comando[20];

    while (1) {
        printf("Ingresa el comando: ");
        scanf("%[^\n]%*c", comando);

        if (strcmp(comando, "exit") == 0) break;

        p = fork();
        if (p == 0) {
            execlp(comando, comando, NULL);
        }
    }
}
