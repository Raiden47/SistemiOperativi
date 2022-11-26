#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <time.h>

#include "procedure.h"

int main() {

	int id_queue, id_shm;
	key_t chiave_shm = IPC_PRIVATE; // TODO definire chiavi;
	key_t chiave_mbx = IPC_PRIVATE; //

	id_shm = shmget(chiave_shm, sizeof(struct MonitorRisultati), IPC_CREAT | 0664); // TODO OTTENERE RISORSE
	id_queue = msgget(chiave_mbx, IPC_CREAT | 0664); //

	if( id_shm < 0 || id_queue < 0) {
		perror("errore creazione risorse");
		exit(1);
	}

	struct MonitorRisultati * ls = shmat(chiave_shm, NULL, 0); //TODO ottenere riferimento al monitor
	if (ls == (void*)-1)
		{perror("Errore nell'acquisizione del riferimento al monitor"); _exit(1);}

	init_monitor( &(ls->m), 2 );

	// TODO inizializzare risorse
	// ls->num_generatori = 0;
	// ls->num_calcolatori = 0;
	// ls->num_scrittori = 0;

	pid_t pid;

	int j;
	for(j=0; j < N_PRINTERS ; j++) {
		// TODO creare processi printer
		pid = fork();

		if (pid == 0){

			_exit(0);
		}
	}

	for(j=0; j < N_CALCOLATORI ; j++) {
		// TDO creare processi calcolatori
		pid = fork();

		if (pid == 0){

			_exit(0);
		}
	}

	for(j=0; j < N_GENERATORI ; j++) {
		// TODO creare processi generatori
		pid = fork();

		if (pid == 0){

			_exit(0);
		}
	}





	for(j=0; j<N_CALCOLATORI+N_GENERATORI+N_PRINTERS; j++)
		// TODO JOIN
		wait(NULL);

	// TODO REMOVE RESOUCES
	remove_monitor(&(ls->m));
	msgctl(chiave_mbx,IPC_RMID,0);
	shmctl(chiave_mbx,IPC_RMID,0);
}
