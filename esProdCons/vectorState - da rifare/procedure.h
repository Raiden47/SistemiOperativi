#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include <sys/types.h>

#define DIM_BUFFER 5
#define N_PRODUTTORI 10
#define N_CONSUMATORI 10


#define IN_USE 0
#define EMPTY 1
#define FULL 2

struct prodCons {
  int buffer[DIM_BUFFER];
  int vector[DIM_BUFFER];
};

int check_state (struct prodCons * bff, int state);
void change_state(struct prodCons * bff, int state, int pos);
void produttore (struct prodCons * bff, int ds_sem);
void consumatore (struct prodCons * bff, int ds_sem);

#endif //_PROCEDURE_H_
