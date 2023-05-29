#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sighand(int signum) {
    printf("Recibí la señal %d\n", signum);
}

int main() {
    int p;

    signal(10, sighand);

    p = fork();

    if (p == 0) {
        while (1) {
            sleep(10);
            kill(getppid(), 10);
        }
    } else {
        while(1) {
            printf("Hola mundo\n");
            sleep(2);
        }
    }
}
