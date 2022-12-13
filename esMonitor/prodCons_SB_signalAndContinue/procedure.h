#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include "monitor_signal_continue.h"

#define NUM_PROD 10
#define NUM_CONS 10

#define W_PC 0
#define K_PC 1

#define CV_PROD 0
#define CV_CONS 1

struct prodCons{
  int buffer;

  int prod;
  int cons;

  Monitor m;
};

void init_buffer(struct prodCons *);
void abilita_prod_cons (struct prodCons * , int , int );
void produttore (struct prodCons *);
void consumatore (struct prodCons *);

#endif //_PROCEDURE_H_
