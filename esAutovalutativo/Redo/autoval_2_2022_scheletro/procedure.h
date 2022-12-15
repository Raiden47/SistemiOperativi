#ifndef HEADER_H
#define HEADER_H

#include "monitor_hoare.h"

#define N_GENERATORI 3
#define N_CALCOLATORI 3
#define N_PRINTERS 3

// TODO DEFINIRE MACRO DI SUPPORTO
#define ADD 0
#define MUL 1
#define DIV 2

#define CV_SUM 0
#define CV_MUL 1
#define cv_DIV 2


struct MonitorRisultati {
	//TODO riempire struttura
	float *ris;
	int dim;

	int sum_op;
	int mult_op;
	int div_op;

	Monitor m;
};


void inserisci_risultato(struct MonitorRisultati * ls, float valore, int operazione);
float* leggi_risultati(struct MonitorRisultati * ls);

typedef struct {
	// TODO DEFINIRE TIPO Messaggio
	long operazione;
	float valore;
} Messaggio;

void calcolo(struct MonitorRisultati * ls, int operazione, int mailbox);
void generazione(int operazione, int mailbox);
void printer(struct MonitorRisultati * ls);

#endif
