#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include "semaphore.h"

#define N_PROC 10
#define N_ELEM 1000
#define N_VAL 10000

int ricerca_min (int vector[], int init_pos);
void genera_array (int vector[]);
int controllo (int vector[]);

#endif //_PROCEDURE_H_
