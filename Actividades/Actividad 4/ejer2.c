#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    int p;

    p = fork();

    if (p == 0) {
        sleep(1);
    } else {
        sleep(20);
    }
}

// ¿En qué estado se encuentra el hijo?, ¿por qué?
// R: La consola indica que está en un estado de defunct,
// esto es porque el proceso hijo terminó antes que el padre
