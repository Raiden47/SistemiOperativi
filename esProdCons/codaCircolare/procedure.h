#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#define DIM_BUFFER 4
#define SPAZIO_DISPONIBILE 0
#define MESSAGGIO_DISPONIBILE 1
#define MUTEX_P 2
#define MUTEX_C 3

#define NUM_PRODUTTORI 5
#define NUM_CONSUMATORI 5

struct prodcons {
  int buffer[DIM_BUFFER];
  int testa;
  int coda;
};

void produttore (struct prodcons *, int);
void consumatore (struct prodcons *, int);

#endif //_PROCEDURE_H_
