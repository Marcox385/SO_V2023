#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int g = 0;

void sighand(int signum) {
    printf("Recibí la señal %d\n", signum);
    g = 5;
}

int main() {
    int p;

    signal(10, sighand);

    p = fork();

    if (p == 0) {
        while (1) {
            sleep(15);
            kill(getppid(), 10);
        }
    } else {
        while(1) {
            while (g > 0) {
                printf("g = %d\n", g);
                sleep(1);
                g--;
            }
            
            while (g == 0); // Espera
        }
    }
}
