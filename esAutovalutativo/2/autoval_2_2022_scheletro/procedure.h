#ifndef HEADER_H
#define HEADER_H

#include "monitor_hoare.h"

#define N_GENERATORI 3
#define N_CALCOLATORI 3
#define N_PRINTERS 3

// TODO DEFINIRE MACRO DI SUPPORTO
#define SPAZIO_DISPONIBILE 0
#define PRELEVA_OPERANDI 1
#define PRELEVA_RISULTATO 2

struct MonitorRisultati {
	//TODO riempire struttura
	int risultati [3];
	// TODO
	Monitor m;
};


void inserisci_risultato(struct MonitorRisultati * ls, float valore, int operazione);
float* leggi_risultati(struct MonitorRisultati * ls);

typedef struct {
	// TODO DEFINIRE TIPO MESSAGGIO
	long type;
	float op;
} Messaggio;

void calcolo(struct MonitorRisultati * ls, int operazione, int mailbox);
void generazione(int operazione, int mailbox);
void printer(struct MonitorRisultati * ls);

#endif
