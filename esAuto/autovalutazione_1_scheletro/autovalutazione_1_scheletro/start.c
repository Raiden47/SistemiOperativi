#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

#include "header.h"


int main(){
	pid_t pid_ex,pid;
	int st,i;
	int shmid,semid;
	BufferCircolare* buf;

	key_t key_shm,key_sem;
	key_shm = //TODO;
	key_sem = //TODO;

	shmid = //TODO
	semid = //TODO
	printf("[MASTER] - Shmid : %d, Semid: %d\n",shmid,semid);

	// TODO
	// Inizializzare risorse

	srand(time(NULL));
	int val;

	for(i = 0; i < NCONS+NPROD; i++){
		// TODO CREARE PROCESSI FIGLI (PRODUTTORI E CONSUMATORI)
		val =  (1+rand()%3);
		sleep(val);

	}
	
	for(i = 0; i < NCONS+NPROD ; i++){
		// TODO JOIN COMPLETAMENTO FIGLI
		printf("[MASTER] - Il processo %d ha terminato l'esecuzione\n",pid_ex);			
	}

	// RIMOZIONE RISORSE
	return 0;
}
