#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include <stdlib.h>

#define N_LETT 10
#define N_SCRITT 10

typedef struct lettScritt{
  int buffer;
  int n_lett;
  int n_scritt;
};

void leggi (struct lettScritt *ls, int ds_sem);
void scrivi (struct lettScritt *ls, int ds_sem);

void inizio_lettura (struct lettScritt *ls, int ds_sem);
void fine_lettura (struct lettScritt *ls, int ds_sem);
void inizio_scrittura (struct lettScritt *ls, int ds_sem);
void fine_scrittura (struct lettScritt *ls, int ds_sem);

int num_gen();
void init_resources (struct lettScritt *ls);

#endif //_PROCEDURE_H_
