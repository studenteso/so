all: start

start: start.c header.h procedure.c
	gcc -pthread -o start start.c procedure.c

clean: 
	rm -f *.o
	rm -f ./start
