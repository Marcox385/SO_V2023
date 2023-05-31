#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int terminado = 0;

void *tfunc(void *args) {
    printf("Hola mundo\n");
    sleep(10);
    printf("Adiós mundo\n");

    terminado = 1;
}

int main() {
    pthread_t tid;

    pthread_create(&tid, NULL, tfunc, NULL);

    while (!terminado);
}
