#include "common.h"

void client(int msgq_guest)
{
	int i;

	/* Inizializzazione Messaggio del processo */
	//TODO
	msg mess = {
		.type = QUEUE_REQ;
		.text = getpid();
	}
	
	/* Invio dei 15 messaggi in ciclo, con sleep(1) tra un messaggio e l'altro */
	//TODO
	for (i = 0 ; i < 15 ; i++){
		msgsnd(msgq_guest, &msg, SIZEOF(msg),0);
		sleep (1);
	}

}
