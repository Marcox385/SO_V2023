/*
    Práctica 4
    Cálculo de ln(1 + x) a través de la serie de Mercator - Versión con mensajes

    Equipo 3
    IS727223 - Paez Aguilar, Carlos Andrés
    IS727272 - Cordero Hernández, Marco Ricardo


    Para compilar incluir la librería m (matemáticas)

    Ejemplo:
        gcc -o msgs msgs.c -lm
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define NPROCS 4 // Número de procesos
#define SERIES_MEMBER_COUNT 200000 // Términos del cálculo
#define IPC_WAIT 0 // Espera bloqueante (se podría utilizar IPC_RMID)

double x = 0.5;  // Desplazamiento en el cálculo (-1, 1]

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
    struct msgbuf mensaje; // Manejador para operaciones de mensajería

    msgrcv(mb_id, &mensaje, sizeof(struct msgbuf), proc_num, IPC_WAIT);

    printf("Proceso %d iniciado\n", proc_num);
    double local_sum = 0; // Resultado parcial de proceso esclavo

    // Ciclo intercalado con múltiplos de NPROCS
    for(i = proc_num - 1; i < SERIES_MEMBER_COUNT; i += NPROCS)
        local_sum += get_member(i + 1, x); // Sumar término de la serie
    
    mensaje.mtype = proc_num;
    mensaje.num = local_sum;
    msgsnd(mb_id, &mensaje, sizeof(struct msgbuf), IPC_WAIT);

    exit(0);
}

// Código para proceso master
void master_proc() {
    int i;
    struct msgbuf mensaje; // Manejador para operaciones de mensajería
    double result = 0.0; // Contenedor para resultados parciales de procesos esclavos
    double holder; // Variable para redireccionar bits de msgrcv de procesos esclavos

    sleep(1);

    for (i = 0; i < NPROCS; i++) {
        mensaje.mtype = i + 1;
        msgsnd(mb_id, &mensaje, sizeof(struct msgbuf), IPC_NOWAIT);
    }

    do {
        holder = msgrcv(mb_id, &mensaje, sizeof(struct msgbuf), 0, IPC_WAIT);  
        result += (double)mensaje.num;
    } while (--i > 0);
    
    mensaje.num = result;
    msgsnd(mb_id, &mensaje, sizeof(struct msgbuf), IPC_WAIT);
    
    exit(0);
}

int main() {
    // Variables para tiempo de ejecución
    long long start_ts;
    long long stop_ts;
    long long elapsed_time;
    long lElapsedTime;
    struct timeval ts;

    // Variables de control
    int i;
    int p;

    double res; // Total del cálculo
    struct msgbuf mensaje; // Contenedor para resultado

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
            proc(i + 1); // Se suma + 1 para manejar el tipo de mensajes
    }

    // Inicio de proceso master
    p = fork();
    if(p==0)
        master_proc();
    
    printf("El recuento de ln(1 + x) miembros de la serie de Mercator es %d\n", SERIES_MEMBER_COUNT);
    printf("El valor del argumento x es %f\n", (double)x);

    for(int i = 0; i < NPROCS; i++)
        wait(NULL);

    // Recibir y almacenar total del cálculo
    msgrcv(mb_id, &mensaje, sizeof(struct msgbuf), 0, IPC_WAIT);
    res = mensaje.num; // Variable omisible pero conservada para legibilidad

    gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec; // Tiempo final
    elapsed_time = stop_ts - start_ts;

    printf("Tiempo = %lld segundos\n", elapsed_time);

    printf("Resultado obtenido -> ln(1 + %f) = %10.8f\n", x, res);
    printf("Resultado esperado -> ln(1 + %f) = %10.8f\n", x, log(1+x));
    printf("TIEMPO DE EJECUCIÓN: %lld segundos\n", elapsed_time);

    // Remover buzón/cola de mensajes
    msgctl(mb_id, IPC_RMID, NULL);
}
