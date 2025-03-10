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
	//Codice wait
	int err;
	struct sembuf sem_buf;
	sem_buf.sem_num = numsem;
	sem_buf.sem_flag = 0;
	sem_buf.sem_op = -1;

	err = semop(id_sem, &sem_buff,1);

	if (err < 0){
		printf("errore WAIT\n");
	}

}


void Signal_Sem (int id_sem,int numsem)     {
	//Codice signal
	int err;
	struct sembuf sem_buf;
	sem_buf.sem_num = numsem;
	sem_buf.sem_flag = 0;
	sem_buf.sem_op = 1;

	err = semop(id_sem,&sem_buf,1);

	if (err < 0){
		printf("Errore SIGNAL\n");
	}
	
}

//Calcolo statistiche
double media(int* v){
	int i;
	double somma;
	somma = 0.0f;
	for(i = 0; i < N;i++){
		somma += v[i];
	}
	return (double)(somma/N);
}

double var(int* v,double media){
	int i;
	double somma_par,temp;
	somma_par = 0.0f;
	for(i = 0; i < N;i++){
		temp = v[i]*v[i];
		somma_par += (temp - media);
	}
	return (double)(somma_par/N-1);
}

// Consumo
void consuma_elementi(int sem, BufferCircolare* buf){
	int val[N];
	double m;
	//Calcola media e varianza
	/*Qua va il codice della sincronizzazione*/

	printf("[Consumatore %d] consumo elementi\n",getpid());
	m = media(val);
	printf("[Consumatore %d] media %f, varianza %f\n",getpid(),m,sqrt(var(val,m)));
}

//Produzione
void produci_elemento(int sem,BufferCircolare* buf){
	int val;
	val =  (1+rand()%11);

	//Produzione valore
	/*Qua va il codice della sincronizzazione*/

	printf("[Produttore %d] ho prodotto %d in posizione %d\n",getpid(),val,buf->testa);
}
