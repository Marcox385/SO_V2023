all: mercator semafor

mercator: mercator.c
	gcc -o mercator mercator.c -lm

semafor: semafor.c
	gcc -o semafor semafor.c  semaphoresarr.c -lm

clean:
	rm mercator semafor
