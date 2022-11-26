#include "procedure.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <time.h>


float* leggi_risultati(struct MonitorRisultati * ls) {

	float* risultati = ls->risultati; //TODO completare

	enter_monitor(&(ls->m));

	printf("[%ld] Lettura - ingresso monitor\n", getpid());

	// TODO lettura
	wait_condition(ls, PRELEVA_RISULTATO);

	signal_condition(ls, PRELEVA_RISULTATO);

	printf("[%ld] Lettura - uscita monitor\n", getpid());

	leave_monitor(&(ls->m));

	return risultati;

}


void inserisci_risultato(struct MonitorRisultati * ls, float valore, int operazione) {

	// TODO scrittura

	enter_monitor(&(ls->m));

	printf("[%ld] Scrittura - ingresso monitor\n", getpid());

	printf("[%ld] Scrittura - valore [%f] operazione %d\n", getpid(),valore, operazione);

	printf("[%ld] Scrittura - uscita monitor\n", getpid());

	leave_monitor(&(ls->m));
	
}

void calcolo(struct MonitorRisultati * ls, int operazione, int mailbox){
	// TODO completa
}

void generazione(int operazione, int mailbox) {
	srand(time(NULL));
	// TODO completa
	Messaggio m;
	m->type = operazione;
	m->op = rand() % 20 + 1;
	msgsnd(mailbox, (void*)&m, sizeof(Messaggio)-sizeof(long), IPC_NOWAIT);
	printf("<--- [%ld] Messagio inviato --->\n", getpid());

}

void printer(struct MonitorRisultati * ls) {
	float* risultati;
	for (int i = 0 ; i < 4; i++) {
		sleep(2);
		risultati = leggi_risultati(ls);
		printf("[%ld] Risultati 1: %f, 2: %f, 3: %f\n",getpid(), risultati[0], risultati[1], risultati[2]);
		//TODO COMPLETA DEALLOCAZIONE risultati
	}
}
