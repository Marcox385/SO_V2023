#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    int p;

    p = fork();

    if (p == 0) {
        kill(getppid(), 9);
    }
}
