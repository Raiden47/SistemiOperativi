#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include <pthread.h>

#define N_THREAD 10

#define N_PROD 3
#define N_CONS 3

typedef struct prodCons{
  long buffer;

  int cons;
  int prod;

  pthread_mutex_t mutex;
  pthread_cond_t cv_cons;
  pthread_cond_t cv_prod;
};

void *Produci (void *);
void *Consuma (void *);

void produzione (struct prodCons *);
void consumo (struct prodCons *);

void inizio_produzione (struct prodCons *);
void fine_produzione (struct prodCons *);
void inizio_consumo (struct prodCons *);
void fine_consumo (struct prodCons *);

void init_buffer (struct prodCons *);
void remove_buffer (struct prodCons *);

#endif //_PROCEDURE_H_
