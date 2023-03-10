all: PC_SB

PC_SB: main.o	procedure.o semaphore.o
	gcc -o PC_SB main.o procedure.o semaphore.o

main.o: main.c
	gcc	-o main.o -c main.c

procedure.o: procedure.c procedure.h
	gcc -o procedure.o -c procedure.c

semaphore.o: semaphore.c semaphore.h
	gcc -o semaphore.o -c semaphore.c

clean:
	rm -f *.o
	rm -f PC_SB
