#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	printf("Aquí comenzamos, soy %d\n", getpid());
	execlp("ps", "ps", NULL);
	printf("Aquí terminamos, soy %d\n", getpid());
}

