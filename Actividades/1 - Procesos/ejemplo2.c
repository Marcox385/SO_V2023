#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	printf("Hola, mi PID es %d\n", getpid());
	fork();
	printf("Otra vez hola desde %d\n", getpid());
	fork();
	printf("Adiós, mi PID es %d\n", getpid());
}

