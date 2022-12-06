			/*----HEADER FILE----*/
#ifndef __HEADER
#define __HEADER

#define SIZE 4

#define LIBERO 0
#define IN_USO 1
#define OCCUPATO 2

#define NPROD 3
#define NCONS 3

typedef struct{
	int chiave;
	int valore;
} ElemBuffer;

typedef struct{
	ElemBuffer elementi[SIZE];
	int stati[SIZE];
} BufferCircolare;

//INSERIRE IDENTIFICATIVI SEMAFORI
#define SPAZIO_DISPONIBILE 0
#define MSG_DISPONIBILE_I 1
#define MSG_DISPONIBILE_II 2
#define MSG_DISPONIBILE_III 3


void Wait_Sem(int, int);
void Signal_Sem (int, int);

void produci(BufferCircolare* buf, int chiave, int semid);
void consuma(BufferCircolare* buf, int chiave, int semid);

#endif
