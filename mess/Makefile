all: start

start: start.o Client Balancer Server1  Server2 Server3
	gcc -o start start.o Client Balancer Server1  Server2 Server3

start.o: start.c header.h
	gcc -c start.c

Balancer.o: Balancer.c header.h
	gcc -c Balancer.c

Balancer: Balancer.o
	gcc -o Balancer Balancer.o

Client.o: Client.c header.h
	gcc -c Client.c

Client: Client.o
	gcc -o Client Client.o

Server1.o: Server1.c header.h
	gcc -c Server1.c

Server1: Server1.o
	gcc -o Server1 Server1.o

Server2.o: Server2.c header.h
	gcc -c Server2.c

Server2: Server2.o
	gcc -o Server2 Server2.o

Server3.o: Server3.c header.h
	gcc -c Server3.c

Server3: Server3.o
	gcc -o Server3 Server3.o

clean:
	rm -f *.o
	rm -f ./start ./Client ./Server1 ./Server2 ./Server3 ./Balancer
