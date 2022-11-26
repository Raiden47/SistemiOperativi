start: main.o procedure.o semaphore.o
	gcc -o prodCons main.o procedure.o semaphore.o

main.o: main.c procedure.h semaphore.h
	gcc -o main.o -c main.c

procedure.o: procedure.c procedure.h
	gcc -o procedure.o -c procedure.c

semaphore.o: semaphore.c semaphore.h
	gcc -o semaphore.o -c semaphore.c

clean:
	rm -f *.o
	rm -f ./prodCons
