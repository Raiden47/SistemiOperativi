all: start

start: main.o procedure.o semaphore.o
	gcc -o prodCons main.o procedure.o semaphore.o

main.o: main.c procedure.h semaphore.h
	gcc -c main.c procedure.h semaphore.h

procedure.o: procedure.c procedure.h
	gcc -c procedure.c procedure.h

semaphore.o: semaphore.c semaphore.h
	gcc -c semaphore.c semaphore.h

clean:
	rm -fr *.o
	rm -fr ./prodCons
