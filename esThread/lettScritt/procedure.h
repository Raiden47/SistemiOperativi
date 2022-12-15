#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_THREAD 10
#define N_LETT 5
#define N_SCRITT 5

struct lettScritt{
  long buffer;

  int num_scritt;
  int num_lett;

  int n_w_s;
  int n_w_l;

  pthread_mutex_t mutex;
  pthread_cond_t cv_scritt;
  pthread_cond_t cv_lett;
};

void init_buffer (struct lettScritt *);
void remove_buffer (struct lettScritt *);

long leggi (struct lettScritt *);
void scrivi (struct lettScritt * , long );

void inizio_lettura (struct lettScritt *);
void fine_lettura (struct lettScritt *);
void inizio_scrittura (struct lettScritt *);
void fine_scrittura (struct lettScritt *);

void *lettore (void *);
void *scrittore (void *);

#endif //_PROCEDURE_H_
