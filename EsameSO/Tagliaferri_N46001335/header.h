			/*----HEADER FILE----*/
#ifndef __HEADER
#define __HEADER

#include "semafori.h"

#define DIM 4

#define SEM_PROD 0
#define SEM_CONS_1 1
#define SEM_CONS_2 2
#define MUTEX_P 3
#define MUTEX_C 4

#define FREE 0
#define IN_USE 1
#define T1 2
#define T2 3

#define NPROD 4
#define NCONS 2

#define PRODS 4
#define CONS 8

typedef struct {
	int buffer[DIM];
	int state[DIM];

	int n_prod;
	int n_cons;

} BufferMutuaEx;

void produci_tipo_1(BufferMutuaEx * buf, int semid, int val);
void produci_tipo_2(BufferMutuaEx * buf, int semid, int val);
void consuma_tipo_1(BufferMutuaEx * buf, int semid);
void consuma_tipo_2(BufferMutuaEx * buf, int semid);



#endif
