#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int i;

int main () {
	int p, retval;

	p = fork();

	if (p == 0) { // 0 cuando es el hijo (del fork)
		printf("Inicia proceso hijo con PID %d\n", getpid());
		for (i = 0; i < 8; i++) {
			printf("En el hijo (%d) i = %d\n", getpid(), i);
			sleep(2);
		}

		exit(5);
	}

	for (i = 4; i > 0; i--) {
		printf("En el padre i = %d\n", i);
		sleep(2);
	}

	p = wait(&retval);
	printf("El hijo %d terminó con código %x\n", p, retval);
}

