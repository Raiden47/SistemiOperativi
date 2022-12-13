#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include "monitor_hoare.h"

#define NUM_LETT 10
#define NUM_SCRITT 10

#define CV_LETT 0
#define CV_SCRITT 1

struct lettScritt{
  int buffer;

  int l_buffer;
  int s_buffer;

  Monitor m;

};

void init_buffer (struct lettScritt *);
void inizio_lettura (struct lettScritt *);
void fine_lettura (struct lettScritt *);
void inizio_scrittura (struct lettScritt *);
void fine_scrittura (struct lettScritt *);
void lettura (struct lettScritt *);
void scrittura (struct lettScritt *, int );

int genera_numero ();


#endif
