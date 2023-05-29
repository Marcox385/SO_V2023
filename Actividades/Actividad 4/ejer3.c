#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    int p;

    p = fork();

    if (p == 0) {
        sleep(20);
    } else {
        sleep(1);
    }
}

// ¿En qué estado se encuentra el padre?, ¿por qué?
// R: 
