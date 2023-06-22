/*
    Práctica 4
    Cálculo de ln(1 + x) a través de la serie de Mercator - Versión con mensajes

    Equipo 3
    IS727223 - Paez Aguilar, Carlos Andrés
    IS727272 - Cordero Hernández, Marco Ricardo


    Para compilar incluir la librería m (matemáticas)

    Ejemplo:
        gcc -o mercator mercator.c -lm
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define NPROCS 4 // Número de procesos
#define SERIES_MEMBER_COUNT 200000 // Términos del cálculo
#define IPC_WAIT 0

double *sums;    // Arreglo de sumas parciales
double x = 0.5;  // Desplazamiento en el cálculo (-1, 1]
int *proc_count; // Conteo de procesos terinados
int *start_all;  // Bandera para inicialización de todos los procesos desde master
double *res;     // Resultado final de la operación

// Componentes para el buzón de mensajes
int mb_id;       // Identificador del buzón

struct msgbuf {  // Estructura para mensajes
    long mtype;  // Tipo de mensaje
    double num;  // Contenido del mensaje
};

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
    struct msgbuf mensaje;
    // while(!(*start_all)); // Espera ocupada

    msgrcv(mb_id, &mensaje, sizeof(struct msgbuf), proc_num, IPC_WAIT);

    printf("Proceso %d iniciado\n", proc_num);
    // sums[proc_num] = 0;
    double local_sum = 0;

    // Ciclo intercalado con múltiplos de NPROCS
    for(i = proc_num; i < SERIES_MEMBER_COUNT; i += NPROCS)
        // sums[proc_num] += get_member(i+1, x); // Sumar término de la serie
        local_sum += get_member(i+1, x); // Sumar término de la serie
    
    // (*proc_count)++; // Indicar que un proceso ha terminado
    mensaje.mtype = i;
    mensaje.num = local_sum;
    msgsnd(mb_id, &mensaje, sizeof(struct msgbuf), IPC_NOWAIT);

    exit(0);
}

// Código para proceso master
void master_proc() {
    int i;
    struct msgbuf mensaje;
    double result = 0;

    sleep(1);
    // *start_all = 1;

    for (i = 0; i < NPROCS; i++) {
        mensaje.mtype = i + 1;
        msgsnd(mb_id, &mensaje, sizeof(struct msgbuf), IPC_NOWAIT);
    }

    // while (*proc_count != NPROCS) {} // Espera ocupada (esperando a procesos individuales)

    for (i = 0; i < NPROCS; i++) {
        msgrcv(mb_id, &mensaje, sizeof(struct msgbuf), i + 1, IPC_WAIT);
        result += mensaje.num;
    }
    
    // Variable y ciclo para sumar resultado final
    // *res = 0;
    // for(i = 0; i < NPROCS; i++)
    //     *res += sums[i];

    printf("DEBUG - RESULT %10.8f\n", result);
    
    exit(0);
}

int main() {
    // int *threadIdPtr; // APUNTADOR NO UTILIZADO

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
    // int shmid;
    // void *shmstart;

    // shmid = shmget(0x1234, NPROCS * sizeof(double) + 2 * sizeof(int), 0666|IPC_CREAT);
    // shmstart = shmat(shmid, NULL, 0);
    // sums = shmstart;
    // proc_count = shmstart + NPROCS * sizeof(double);
    // start_all = shmstart + NPROCS * sizeof(double) + sizeof(int);
    // res = shmstart + NPROCS * sizeof(double) + 2 * sizeof(int);
    
    // *proc_count = 0;
    // *start_all = 0;

    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec; // Tiempo inicial

    // Inicialización de buzón
    mb_id = msgget(0x4495, 0666|IPC_CREAT);
    if(mb_id == -1) {
		fprintf(stderr, "No se pudo crear el buzón\n");
		exit(1);
	}

    // Inicio de procesos individuales
    for(i = 0; i < NPROCS; i++) {
        p = fork();
        if(p==0)
            proc(i + 1);
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
    // shmdt(shmstart);
    // shmctl(shmid,IPC_RMID,NULL);

    // Remover buzón
    msgctl(mb_id, IPC_RMID, NULL);
}
