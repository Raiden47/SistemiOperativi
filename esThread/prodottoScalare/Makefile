prodScalare: main.o procedure.o
	gcc -pthread -o prodScalare main.o procedure.o

main.o: main.c procedure.h
	gcc -o main.o -c main.c

procedure.o: procedure.c procedure.h
	gcc -o procedure.o -c procedure.c

clean:
	rm -f prodScalare
	rm -f *.o
