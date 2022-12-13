#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include "monitor_signal_continue.h"

#define DIM_BUFFER 5

#define FREE 0
#define IN_USE 1
#define FULL 2

#define NUM_PROD 10
#define NUM_CONS 10

#define CV_PROD 0
#define CV_CONS 1

struct prodCons {
  int buffer [DIM_BUFFER];
  int state [DIM_BUFFER];

  int num_free;
  int num_full;

  Monitor m;
};

void init_buffer (struct prodCons *);
int check_state (struct prodCons *, int );
void produttore (struct prodCons * , int );
void consumatore (struct prodCons * );

#endif //_PROCEDURE_H_
