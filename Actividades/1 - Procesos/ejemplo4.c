#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int i;

int main () {
	int p;

	p = fork();

	if (p == 0) { // 0 cuando es el hijo (del fork)
		for (i = 0; i < 8; i++) {
			printf("En el hijo i = %d\n", i);
			sleep(2);
		}
	} else { // Cualquier otra cosa cuando sea el padre
		for (i = 4; i > 0; i--) {
			printf("En el padre i = %d\n", i);
			sleep(2);
		}
	}
}

