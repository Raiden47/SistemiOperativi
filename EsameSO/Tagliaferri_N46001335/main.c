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
	BufferMutuaEx* buf;

	key_t key_shm,key_sem;
	key_shm = IPC_PRIVATE;	// TODO
	key_sem = IPC_PRIVATE;	// TODO

	shmid = shmget(key_shm, sizeof(BufferMutuaEx *), IPC_CREAT | 0664);	// TODO
	semid = semget(key_sem, 5, IPC_CREAT | 0664); // TODO

	printf("[MASTER] - Shmid : %d, Semid: %d\n",shmid,semid);

	// TODO: inizializzare semafori

	semctl(semid, SEM_PROD, SETVAL, DIM);
	semctl(semid, SEM_CONS_1, SETVAL, 0);
	semctl(semid, SEM_CONS_2, SETVAL, 0);
	semctl(semid, MUTEX_P, SETVAL, 1);
	semctl(semid, MUTEX_C, SETVAL, 1);


	buf = shmat(shmid,NULL,0);

	// TODO: inizializzazione della struttura

	for (i = 0 ; i < DIM ; i++)
		buf->state[i] = FREE;

	buf->n_prod = DIM;
	buf->n_cons = 0;

	srand(time(NULL));

	for(i = 0; i < NPROD; i++){
		pid = fork();

		if (pid == 0){
			if (i%2)
				for (int j = 0 ; j < PRODS ; j++)
					produci_tipo_1(buf, semid,rand()%90+10);
			else
				for (int j = 0 ; j < PRODS ; j++)
					produci_tipo_2(buf, semid,rand()%90+10);
			exit (0);
		}
		// TODO: ogni figlio produttore (1 e 2) fa PRODS produzioni

	}

	for(i = 0; i < NCONS; i++){
		pid = fork();

		if (pid == 0){
			if (i%2)
				for (int j = 0 ; j < CONS ; j++)
					consuma_tipo_1(buf, semid);
			else
				for (int j = 0 ; j < CONS ; j++)
					consuma_tipo_2(buf, semid);
			exit (0);
		}
		// TODO: ogni figlio consumatore (1 e 2) fa CONS consumi

	}

	// TODO: attesa completamento figli

	for (i = 0 ; i < NPROD+NCONS ; i++){
		wait(&st);
		printf("<--- Processo figlio terminato con stato [%d] --->\n", st>>8);
	}

	// TODO: rimozione strutture
	shmctl(shmid,IPC_RMID, 0);
	semctl(semid, 5, IPC_RMID);

	return 0;
}
