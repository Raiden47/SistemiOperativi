all: prodCons

prodCons: main.o semaphore.o
	gcc -o prodCons main.o procedure.o semaphore.o

main.o: main.c semaphore.h procedure.h
	gcc -c main.c semaphore.h

procedure.o: procedure.c procedure.h
	gcc -c procedure.c procedure.h

semaphore.o: semaphore.c semaphore.h
	gcc -c semaphore.c semaphore.h

clean:
	rm -fr *.o
	rm -fr ./prodCons
