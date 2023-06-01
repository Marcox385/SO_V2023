/*
* El siguiente programa obtiene el número de cores en el sistema
* en máquinas basadas en Unix.
* La ventaja que tiene esto sobre un #define es que obtiene este
* dato en tiempo de ejecución para programas más flexibles.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	int NTHREADS = sysconf(_SC_NPROCESSORS_ONLN);

	printf("Cores: %d\n", NTHREADS);
}
