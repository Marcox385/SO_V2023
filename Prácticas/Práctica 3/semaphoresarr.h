#include <sys/sem.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 

#define SEM_ID int

void semwait(int semid,int nsem);
void semsignal(int semid,int nsem);
int createsemarray(int key, int nsems);
void initsem(int semid,int semnum,int value);
void erasesem(int semid);
