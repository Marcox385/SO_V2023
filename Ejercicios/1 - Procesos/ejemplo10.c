#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int p;
	printf("Aquí comenzamos, soy %d\n", getpid());
	p = fork();

	if (p == 0) execlp("ps", "ps", NULL);
	wait(NULL);
	printf("Aquí terminamos, soy %d\n", getpid());
}

