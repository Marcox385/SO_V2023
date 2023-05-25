#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	printf("Aquí comenzamos, soy %d\n", getpid());
	system("ps");
	printf("Aquí terminamos, soy %d\n", getpid());
}

