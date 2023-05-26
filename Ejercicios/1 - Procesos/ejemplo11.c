#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int i;
	
	printf("Este programa recibió %d argumentos de la línea de comandos\n", argc);

	for (i = 0; i < argc; i++) {
		printf(" %d ) %s \n", i, argv[i]);
	}	
}

