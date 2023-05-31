#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 4

void *tfunc(void *args) {
    printf("Hola mundo\n");
    sleep(10);
    printf("Adiós mundo\n");
}

int main() {
    pthread_t tid[NTHREADS];
    int i;

    for (i = 0; i < NTHREADS; i++)
        pthread_create(&tid[i], NULL, tfunc, NULL);

    for (i = 0; i < NTHREADS; i++)
        pthread_join(tid[i], NULL);
}
