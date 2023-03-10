#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "monitor_signal_continue.h"

#define N_LET 10
#define N_SCR 10
#define N_PROC 20

#define CV_L 0
#define CV_S 1

typedef struct letScr{

  int buffer;

  int n_let;
  int n_scr;

  Monitor m;
};

void leggi (struct letScr *ls);
void scrivi (struct letScr *ls);

void inizio_lettura (struct letScr *ls);
void fine_lettura (struct letScr *ls);
void inizio_scrittura (struct letScr *ls);
void fine_scrittura (struct letScr *ls);

void init_buffer (struct letScr *ls);

#endif //_PROCEDURE_H_
