#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include <pthread.h>

#define N_THREAD 10

#define N_LET 5
#define N_SCR 5

typedef struct letScr{
  int buffer;

  int num_let;
  int num_scr;
  int scr_queue;

  pthread_mutex_t mutex;
  pthread_cond_t cv_let;
  pthread_cond_t cv_scr;
};

void *Lettore (void *);
void *Scrittore (void *);

void leggi (struct letScr *);
void scrivi (struct letScr *);

void inizio_lettura (struct letScr *);
void fine_lettura (struct letScr *);
void inizio_scrittura (struct letScr *);
void fine_scrittura (struct letScr *);

void init_buffer (struct letScr *);
void remove_buffer (struct letScr *);

#endif //_PROCEDURE_H_
