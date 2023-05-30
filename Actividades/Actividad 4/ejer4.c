#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    int i, p;
    p = getpid();

    printf("Soy el proceso padre %d\n", p);

    for(i = 0; i < 2; i++) {
        int h = fork();

        if(h == 0) {
            printf("Soy un proceso hijo %d - Padre %d\n", getpid(), getppid());

            int j;
            for(j = 0; j < 3; j++) {
                int n = fork();

                if(n == 0) {
                    printf("Soy un proceso nieto %d - Padre %d\n", getpid(), getppid());
                    sleep(2);
                    exit(0);
                }

                wait(NULL);
            }

            sleep(2);
            exit(0);
        }

        wait(NULL);
    }

    if(p_pid == getpid()) {
        sleep(5);
        printf("Proceso padre %d matando los procesos de los hijos y los nietos\n", p_pid);
        // matando los hijos se matan a los procesos que dependen de ellos (los nietos)
        kill(-1 * p, 9);
        sleep(5);     
    }

    return 0;
}