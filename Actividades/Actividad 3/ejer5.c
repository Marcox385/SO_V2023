/*
* 5.- Repite el ejercicio anterior, pero ahora no podrás usar la llamada al sistema
* system(), por lo que será necesario que crees un nuevo proceso (hijo) el cuál ejecutará
* el programa que indicaste; Una vez que termine el programa de ejecutarse permitirá al
* usuario introducir otro programa a ejecutarse, esto terminará cuando el usuario
* introduzca exit.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int p;
    char comando[20];

    while (1) {
        printf("Ingresa el comando: ");
        scanf("%[^\n]%*c", comando);

        if (strcmp(comando, "exit") == 0) break;

        p = fork();
        if (p == 0) {
            execlp(comando, comando, NULL);
        }
        wait(NULL);
    }
}
