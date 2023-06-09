#include <stdio.h>
#include "semaphoresarr.h"

void semwait(int semid, int nsem)
{
	struct sembuf s;
	s.sem_num = nsem; // número de semáforo en el arreglo
	s.sem_op = -1;	// -1 es un decremento el cual significa la llamada u operación wait
	s.sem_flg = 0;
	
	semop(semid, &s, 1);
	return;
}
	
void semsignal(int semid, int nsem)
{
	struct sembuf s;
	s.sem_num = nsem; // número de semáforo en el arreglo
	s.sem_op = 1;		// 1 es un incremento el cual significa la llamada u operación signal
	s.sem_flg = 0;
	
	semop(semid, &s, 1);
	return;
}

int createsemarray(int key, int nsems)
{
	int semid;			    // 110 110 110   RW-RW-RW-
	semid=semget(key, nsems, 0666|IPC_CREAT); // Solicitar un arreglo de semáforos al SO
	return(semid);
}

void initsem(int semid, int semnum, int value)
{
	semctl(semid, semnum, SETVAL, value);
	int value2 = semctl(semid, semnum, GETVAL,0);
	printf("semid: %d, semnum: %d, value: %d\n", semid, semnum, value2);	
}

void erasesem(int semid)
{
	semctl(semid, 0, IPC_RMID, 0);	// Eliminar el arreglo de semaforos
	return;
}

// Función creada para obtener valores de control individuales de un semáforo a petición
int getvalsem(int semid, int semnum)
{
	int value;
	value = semctl(semid, semnum, GETVAL, 0);
	return(value);
}
