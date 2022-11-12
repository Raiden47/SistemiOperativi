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
#include <math.h>

//Procedure per la sincronizzazione sui semafori

void Wait_Sem(int id_sem, int numsem)     {
	struct sembuf sem_buf;
	sem_buf.sem_num = numsem;
	sem_buf.sem_op = -1;
	sem_buf.sem_flg = 0;
	semop(id_sem,&sem_buf,1);
}


void Signal_Sem (int id_sem,int numsem)     {
	struct sembuf sem_buf;
	sem_buf.sem_num = numsem;
	sem_buf.sem_op = 1;
	sem_buf.sem_flg = 0;
	semop(id_sem,&sem_buf,1);

}

// Consumo
void consuma(BufferCircolare* buf, int chiave, int semid){
	printf("[Consumatore %d] iniziato con chiave %d \n",getpid(), chiave);
	int sem;
	int value;
	int index;

	for(int i=0; i<3; i++){
		// TODO completare consumazione
		printf("[Consumatore %d] consumo elemento in posizione %d\n",getpid(), index);	
		printf("[Consumatore %d] valore letto: %d\n",getpid(), value);
	}
}

//Produzione
void produci(BufferCircolare* buf, int chiave, int semid){
	printf("[Produttore %d] iniziato con chiave %d\n",getpid(), chiave);
	int val_sleep;
	int value;
	int sem;
	int index;

	for(int i=0; i<3; i++){
		// TODO COMPLETARE PRODUZIONE
		printf("[Produttore %d] entrato con chiave %d \n",getpid(), chiave);
		printf("[Produttore %d] ho prodotto %d, con chiave %d, in posizione %d\n",getpid(),value, chiave, index);
	}
}
