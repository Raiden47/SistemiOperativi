#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include "monitor_signal_continue.h"

#define N_SCR 5
#define N_LTT 5

#define CV_SCR 0
#define CV_LTT 1

struct lettScritt{
  int buffer;

  int n_scritt;
  int n_lett;

  Monitor m;
};

void init_buffer (struct lettScritt *);
void leggi (struct lettScritt *);
void scrivi (struct lettScritt *);

#endif //_PROCEDURE_H_
