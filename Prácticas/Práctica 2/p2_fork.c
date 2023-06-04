/*
    Práctica 2
    Cálculo de PI a través de regla del trapecio - Versión con Procesos

    Equipo 3
    IS727223 - Paez Aguilar, Carlos Andrés
    IS727272 - Cordero Hernández, Marco Ricardo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHOW_OUTPUT 0
#define ITERS 1000000000
#define NPROCESS 4
#define KEY 999999

double f(double x) {
    return sqrt(1 - pow(x, 2));
}

int main() {
    double acc = 0;
    int PI_FACTOR = 4;

    long long start_ts;
	long long stop_ts;
	long long elapsed_time;
	long lElapsedTime;
	struct timeval ts;

    int shmid;
    double *shared_memory;

    double factor = 1.0/ITERS;

    shmid = shmget(KEY, sizeof(double) * 4, IPC_CREAT | 0666);
    shared_memory = (double *) shmat(shmid, NULL, 0);
    gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec; // Tiempo inicial

    //Inicio de los procesos
    for(int i = 0; i < NPROCESS; i++) {
        int pid = fork();

        //Proceso hijo
        if(pid == 0) {
            // Inicializar la suma y los límites de la iteración
            double p_sum = 0.0;
            int start = i * (ITERS / NPROCESS);
            int end = (i + 1) * (ITERS / NPROCESS);

            // Función para calcular la suma parcial
            for (int j = start; j < end; j++) {
                p_sum += factor * f(((2*j + 1.0)/ITERS)/2);
            }
            // printf("suma parcial %d: %lf\n", i, p_sum);

            // Guardar la suma parcial en la memoria compartida
            shared_memory[i] = p_sum;
            // Salir del proceso hijo
            exit(0);
        }
    }

    //Esperar a que terminen los procesos hijos
    for(int i = 0; i < NPROCESS; i++) {
        wait(NULL);
        sleep(1);
        printf("suma parcial %d: %lf\n", i, shared_memory[i]);
        acc += shared_memory[i];
    }

    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, NULL);

    acc *= PI_FACTOR;

    gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec; // Tiempo final

	elapsed_time = stop_ts - start_ts;
	printf("\33[2K\rResultado = %.30lf\n", acc);
	printf("------------------------------\n");
	printf("TIEMPO TOTAL, %lld segundos\n", elapsed_time);
}
