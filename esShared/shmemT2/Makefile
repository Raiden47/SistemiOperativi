all: start

start: main.o
	gcc -o shmTest main.o
	
main.o: main.c
	gcc -c main.c
	
clear:
	rm -f *.o
	rm -f ./shmTest
