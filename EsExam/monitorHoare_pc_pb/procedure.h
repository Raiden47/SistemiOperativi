#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>

#include "monitor_hoare.h"

#define DIM_BUFFER 5

#define FREE 0
#define IN_USE 1
#define FULL 2

#define CV_CONS 0
#define CV_PROD 1

#define DIM_PROD 10
#define DIM_CONS 10

typedef struct prodcons{
  int buffer [DIM_BUFFER];
  int state [DIM_BUFFER];

  int num_free;
  int num_full;

  Monitor m;
};

void produci (struct prodcons *pc);
void consuma (struct prodcons *pc);

int check_state (struct prodcons *pc, int st);

#endif //_PROCEDURE_H_
