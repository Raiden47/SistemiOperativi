#include "common.h"

void client(int msgq_guest)
{
	int i;
	struct msg mess;
	mess.type = CLIENT;
	int queue = msgget(IPC_PRIVATE | IPC_CREAT | 0664);

	/* Inizializzazione Messaggio del processo */
	//TODO

	/* Invio dei 15 messaggi in ciclo, con sleep(1) tra un messaggio e l'altro */
	//TODO
}
