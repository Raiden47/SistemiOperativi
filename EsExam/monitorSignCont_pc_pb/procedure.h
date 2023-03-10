#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#include "monitor_signal_continue.h"

#define DIM_BUFFER 5

#define FREE 0
#define IN_USE 1
#define FULL 2

#define CV_PROD 0
#define CV_CONS 1

#define N_PROD 10
#define N_CONS 10

typedef struct prodCons{
  int buffer [DIM_BUFFER];
  int state [DIM_BUFFER];

  int n_free;
  int n_full;

  Monitor m;
} ;

void init_buffer (struct prodCons *pc);
void produci (struct prodCons *pc);
void consuma (struct prodCons *pc);
int check_state (struct prodCons *pc, int st);

#endif //_PROCEDURE_H_
