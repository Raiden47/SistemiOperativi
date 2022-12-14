#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include <pthread.h>

#define DIM 5
#define NUM_THR 5

struct vectors {
  int v1[DIM];
  int v2[DIM];
};

struct t_par{
  //struct vectors * vett;
  int v1[DIM];
  int v2[DIM];

  int index;
  int t_sync;

  pthread_mutex_t mutex;
  pthread_cond_t cv_calc;
};

void init_buffer (struct t_par *);

#endif //_PROCEDURE_H_
