			/*----IMPLEMENTAZIONE DELLE PROCEDURE----*/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "semafori.h"
#include <math.h>

void produci_tipo_1(BufferMutuaEx * buf, int semid, int value) {

	// TODO: completare produzione 1

	Wait_Sem(semid, MUTEX_P);

	if (buf->n_prod <= 0)
		Wait_Sem(semid,SEM_PROD);

	buf->n_prod--;

	int index = 0;
	while (index < DIM && buf->state[index] != FREE)
		index++;

	buf->state[index] = IN_USE;

	Signal_Sem(semid,MUTEX_P);

	sleep(rand()%3+1);
	buf->buffer[index] = value;
	printf("[Produttore %d] ho prodotto %d di tipo 1, in posizione %d\n", getpid(), value, index);

	Wait_Sem(semid, MUTEX_P);

	buf->state[index] = T1;
	buf->n_cons++;

	Signal_Sem(semid,SEM_CONS_1);
	Signal_Sem(semid,MUTEX_P);
}

void produci_tipo_2(BufferMutuaEx * buf, int semid, int value) {

	// TODO: completare produzione 2

	Wait_Sem(semid, MUTEX_P);

	if (buf->n_prod <= 0)
		Wait_Sem(semid,SEM_PROD);

	buf->n_prod--;

	int index = 0;
	while (index < DIM && buf->state[index] != FREE)
		index++;

	buf->state[index] = IN_USE;

	Signal_Sem(semid,MUTEX_P);

	sleep(rand()%3+1);
	buf->buffer[index] = value;
	printf("[Produttore %d] ho prodotto %d di tipo 2, in posizione %d\n", getpid(), value, index);

	Wait_Sem(semid, MUTEX_P);

	buf->state[index] = T2;
	buf->n_cons++;

	Signal_Sem(semid,SEM_CONS_2);
	Signal_Sem(semid,MUTEX_P);



}

void consuma_tipo_1(BufferMutuaEx * buf, int semid) {

	// TODO: completare consumo 1

	Wait_Sem (semid, MUTEX_C);

	if (buf->n_cons == 0)
		Wait_Sem(semid, SEM_CONS_1);

	buf->n_cons--;

	int index = 0;
	int value;
	while (index < DIM && buf->state[index] != T1)
		index++;

	buf->state[index] = IN_USE;

	Signal_Sem(semid, MUTEX_C);

	value = buf->buffer[index];

	sleep(rand()%3+1);
	printf("[Consumatore %d] consumo elemento %d di tipo 1 in posizione %d\n",getpid(), value, index);

	Wait_Sem(semid, MUTEX_C);

	buf->state[index] = FREE;
	buf->n_prod++;

	Signal_Sem(semid, SEM_PROD);
	Signal_Sem(semid, MUTEX_C);

}

void consuma_tipo_2(BufferMutuaEx * buf, int semid) {

	// TODO: completare consumo 2

	Wait_Sem (semid, MUTEX_C);

	if (buf->n_cons == 0)
		Wait_Sem(semid, SEM_CONS_2);

	buf->n_cons--;

	int index = 0;
	int value;
	while (index < DIM && buf->state[index] != T2)
		index++;

	buf->state[index] = IN_USE;

	Signal_Sem(semid, MUTEX_C);

	sleep(rand()%3+1);
	value = buf->buffer[index];

	printf("[Consumatore %d] consumo elemento %d di tipo 2 in posizione %d\n",getpid(), value, index);

	Wait_Sem(semid, MUTEX_C);

	buf->state[index] = FREE;
	buf->n_prod++;

	Signal_Sem(semid, SEM_PROD);
	Signal_Sem(semid, MUTEX_C);



}
