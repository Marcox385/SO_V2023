#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sighandler(int signum) {
    printf("Recibí la señal %d\n", signum);
}

int main() {
    signal(SIGINT, sighandler);
    while(1) {
        printf("Hola mundo\n");
        sleep(1);
    }
}
