all: start

start: start.o monitor.o procedure.o
	gcc -o start start.o monitor.o procedure.o

start.o: start.c header.h 
	gcc -c start.c

monitor.o: monitor.c monitor.h
	gcc -c monitor.c

procedure.o: procedure.c header.h 
	gcc -c procedure.c

clean:
	rm -f *.o
	rm -f ./start
