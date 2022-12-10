all: cmMultyProc P1 P2 P3

cmMultyProc: main.o procedure.o
	gcc -o cmMultyProc main.o procedure.o

P1: main1.o procedure.o
	gcc -o P1 main1.o procedure.o

P2: main2.o procedure.o
	gcc -o P2 main2.o procedure.o

P3: main3.o procedure.o
	gcc -o P3 main3.o procedure.o

main.o: main.c procedure.h
	gcc -o main.o -c main.c

main1.o: main1.c procedure.h
	gcc -o main1.o -c main1.c

main2.o: main2.c procedure.h
	gcc -o main2.o -c main2.c

main3.o: main3.c procedure.h
	gcc -o main3.o -c main3.c

procedure.o: procedure.c procedure.h
	gcc -o procedure.o -c procedure.c

clean:
	rm -f *.o
	rm -f P1
	rm -f P2
	rm -f P3
	rm -f cmMultyProc
