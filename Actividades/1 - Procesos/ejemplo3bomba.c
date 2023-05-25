#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	int i;

	for (i = 0; i < 7; i++) fork();

	printf("Fin proceso %d\n", getpid());
}

