			/*----HEADER FILE----*/
#ifndef __HEADER
#define __HEADER

#define N 5

typedef struct{
	int elementi[N];
	int testa;
	int coda;
} BufferCircolare;

//INSERIRE VARIABILI CHE SERVONO


void Wait_Sem(int, int);
void Signal_Sem (int, int);

void produci_elemento(int semid,BufferCircolare* buf);
void consuma_elementi(int semid, BufferCircolare* buf);

#endif
