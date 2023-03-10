#ifndef __PROCEDURE_H__
#define __PROCEDURE_H__

#include <unistd.h>

#include <sys/wait.h>

#define N_OP 20
#define N_PROC 2

void produci (int *sh_num, int ds_sem);
void consuma (int *sh_num, int ds_sem);

int genera_num();

#endif //__PROCEDURE_H__
