codeMessaggi: main.o procedure.o
	gcc -o codeMessaggi main.o procedure.o

main.0: main.c procedure.h
	gcc -o main.o -c main.c

procedure.o: procedure.c procedure.h
	gcc -o procedure.o -c procedure.c

clean:
	rm -f *.o
	rm -f codeMessaggi
