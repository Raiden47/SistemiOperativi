all: PT_LS

PT_LS: main.o procedure.o
	gcc -pthread -o PT_LS main.o procedure.o

main.o: main.c
	gcc -o main.o -c main.c

procedure.o: procedure.c procedure.h
	gcc -o procedure.o -c procedure.c

clean:
	rm -f *.o
	rm -f PT_LS
