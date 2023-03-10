all: CM_AS

CM_AS: main.o procedure.o
	gcc -o CM_AS main.o procedure.o

main.o: main.c
	gcc -o main.o -c main.c

procedure.o: procedure.c procedure.h
	gcc -o procedure.o -c procedure.c

clean:
	rm -f *.o
	rm -f CM_AS
