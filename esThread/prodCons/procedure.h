#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include <stdbool.h>
#include <pthread.h>

#define NUM_PROD 3
#define NUM_CONS 3

#define N_THREADS 10

struct prodCons{
  long buffer;

  int cons;
  int prod;

  pthread_mutex_t mutex;
  pthread_cond_t cv_prod;
  pthread_cond_t cv_cons;
};

void *produttore (void *);
void *consumatore (void *);

void produci (struct prodCons * , long );
long consuma (struct prodCons *);

void init_buffer (struct prodCons *);
void remove_buffer (struct prodCons *);
bool check_state (int );

void inizio_produzione (struct prodCons *);
void fine_produzione (struct prodCons *);
void inizio_consumo (struct prodCons *);
void fine_consumo (struct prodCons *);

#endif //_PROCEDURE_H_
