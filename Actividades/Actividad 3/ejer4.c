/*
* Desarrolla un programa que solicite al usuario una cadena de caracteres, esa cadena
* será el nombre de un programa a ejecutarse, una vez que este programa termine de
* ejecutarse permitirá al usuario introducir otro programa a ejecutarse, esto terminará
* cuando el usuario introduzca exit. Para este ejercicio utiliza la llamada al sistema
* system(). En este ejercicio estamos haciendo nuestro primer shell o intérprete de comandos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    char comando[20];

    while (strcmp(comando, "exit") != 0) {
        printf("Ingresa el comando: ");
        scanf("%[^\n]%*c", comando);

        system(comando);
    }
}
