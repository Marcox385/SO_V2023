/*
    Para compilar incluir la librería m (matemáticas)

    Ejemplo:
        gcc -o mercator mercator.c -lm
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include "semaphoresarr.h"

#define NPROCS 4 // Número de procesos
#define SERIES_MEMBER_COUNT 200000 // Términos del cálculo
#define SYNC1 0 // Semáforo para sincronización
#define SYNC2 1 // Semáforo para sincronización

double *sums; // Arreglo de sumas parciales
double x = 0.5; // Desplazamiento en el cálculo (-1, 1]
int *proc_count; // Conteo de procesos terinados
int *start_all; // Bandera para inicialización de todos los procesos desde master
double *res; // Resultado final de la operación
int semarr;


// Función para obtener término de la serie
double get_member(int n, double x) {
    int i;
    double numerator = 1;

    // Ciclo para obtener potencia
    for(i = 0; i < n; i++)
        numerator = numerator * x;

    // Número signado dependiendo del término de la serie
    if (n % 2 == 0)
        return ( - numerator / n );
    else
        return numerator / n;
}

// Código para procesos individuales
void proc(int proc_num) {
    int i;
    semwait(semarr, SYNC1); 
    printf("Proceso %d iniciado\n", proc_num);
    sums[proc_num] = 0;

    // Ciclo intercalado con múltiplos de NPROCS
    for(i = proc_num; i < SERIES_MEMBER_COUNT; i += NPROCS)
        sums[proc_num] += get_member(i+1, x); // Sumar término de la serie
    semsignal(semarr, SYNC1);
    semsignal(semarr, SYNC2); // Indicar que un proceso ha terminado

    exit(0);
}

// Código para proceso master
void master_proc() {
    int i;

    sleep(1);
    semsignal(semarr, SYNC1); 

    semwait(semarr, SYNC2);    
    // Variable y ciclo para sumar resultado final
    *res = 0;
    for(i = 0; i < NPROCS; i++)
        *res += sums[i];
    
    exit(0);
}

int main() {
    int *threadIdPtr; // APUNTADOR NO UTILIZADO

    // Variables para tiempo de ejecución
    long long start_ts;
    long long stop_ts;
    long long elapsed_time;
    long lElapsedTime;
    struct timeval ts;

    // Variables de control
    int i;
    int p;

    // Variables de memoria compartida
    int shmid;
    void *shmstart;

    //Semaphores
    semarr = createsemarray(0x4321, 2);

    // Inicialización de semáforos
    initsem(semarr, SYNC1, 0);
    initsem(semarr, SYNC2, 0);

    // Inicialización de memoria compartida
    shmid = shmget(0x1234, NPROCS * sizeof(double) + 2 * sizeof(int), 0666|IPC_CREAT);
    shmstart = shmat(shmid, NULL, 0);
    sums = shmstart;
    proc_count = shmstart + NPROCS * sizeof(double);
    start_all = shmstart + NPROCS * sizeof(double) + sizeof(int);
    res = shmstart + NPROCS * sizeof(double) + 2 * sizeof(int);
    
    *proc_count = 0;
    *start_all = 0;

    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec; // Tiempo inicial

    // Inicio de procesos individuales
    for(i = 0; i < NPROCS; i++) {
        p = fork();
        if(p==0)
            proc(i);
    }

    // Inicio de proceso master
    p = fork();
    if(p==0)
        master_proc();
    
    printf("El recuento de ln(1 + x) miembros de la serie de Mercator es %d\n", SERIES_MEMBER_COUNT);
    printf("El valor del argumento x es %f\n", (double)x);

    for(int i = 0; i < NPROCS + 1; i++)
        wait(NULL);

    gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec; // Tiempo final
    elapsed_time = stop_ts - start_ts;

    printf("Tiempo = %lld segundos\n", elapsed_time);

    printf("El resultado es %10.8f\n", *res);
    printf("Llamando a la función ln(1 + %f) = %10.8f\n", x, log(1+x));
    printf("TIEMPO DE EJECUCIÓN: %lld segundos\n", elapsed_time);
    
    // Remover memoria compartida
    shmdt(shmstart);
    shmctl(shmid,IPC_RMID,NULL);
}
