#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "monitor_hoare.h"

#define N_LETT 10
#define N_SCRITT 10

#define CV_LETT 0
#define CV_SCRITT 1

typedef struct lettScritt{
  int buffer;

  int n_lett;
  int n_scritt;

  Monitor m;
};

void init_buffer(struct lettScritt *);
void leggi (struct lettScritt *);

void inizio_lettura (struct lettScritt *);
void fine_lettura (struct lettScritt *);
void inizio_scrittura (struct lettScritt *);
void fine_scrittura (struct lettScritt *);

void scrivi (struct lettScritt *);

#endif // _PROCEDURE_H_
