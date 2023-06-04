all: p1_serial p1_hilos

p1_serial: p1_serial.c
	gcc -o p1_serial p1_serial.c -lm

p1_hilos: p1_hilos.c
	gcc -o p1_hilos p1_hilos.c -lm -lpthread

clean:
	rm p1_serial p1_hilos