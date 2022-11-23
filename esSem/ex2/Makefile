all: sem

sem: main.o semaphore.o procedure.o
	gcc -o sem main.o semaphore.o procedure.o

main.o: main.o
	gcc -c main.c semaphore.h procedure.h

semaphore.o: semaphore.c semaphore.h
	gcc -c semaphore.c semaphore.h

procedure.o: procedure.c procedure.h semaphore.h
	gcc -c procedure.c procedure.h semaphore.h

clean:
	rm -f *.o
	rm -f *.gch
	rm -f ./sem
