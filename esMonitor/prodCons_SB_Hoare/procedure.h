#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include "monitor_hoare.h"

#define NUM_PRODUTTORI 10
#define NUM_CONSUMATORI 10

#define CV_PROD 0
#define CV_CONS 1

struct prodCons {
  int buffer;

  int buffer_libero;
  int buffer_occupato;

  Monitor m;
};

void produzione (struct prodCons *, int );
void consumazione (struct prodCons * );

#endif //_PROCEDURE_H_
