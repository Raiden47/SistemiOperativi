#include "common.h"
#include <sys/wait.h>

#define NR_CLIENT  5

/* ID - Code di Messaggi */
int msgq_guest;
int msgq_print;

int main(int argc,char*argv[])
{
	int i;
	/*Richiesta code di messaggi IPC*/
	msgq_guest = msgget(IPC_PRIVATE, IPC_CREAT | 0664);
	msgq_print = msgget(IPC_PRIVATE, IPC_CREAT | 0664); 

	/*Creazione processo 'printer'*/
	//TODO

	/*Creazione processo 'server'*/
	//TODO

	/*Creazione processi 'client'*/
	//TODO

	/*Attesa terminazione dei client*/
	//TODO;

	/*Invio messaggio di terminazione al server*/
	//TODO

	/*Attesa terminazione processi 'server' e 'printer'*/
	for(i=0; i<2; i++)
		wait(0);

	/*Rimozione code IPC e uscita*/
	//TODO

	return 0;
}
