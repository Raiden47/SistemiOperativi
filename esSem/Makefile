all: sem

sem: main.o semaphore.o
	gcc -o main.o semaphore.o

main.o:	main.c semaphore.h
	gcc -c main.c -o main.o

semaphore.o: semaphore.c semaphore.h
	gcc -c semaphore.c -o semaphore.o

clean:
	rm -f *.0
	rm -f sem
