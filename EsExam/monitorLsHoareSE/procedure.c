#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "procedure.h"

void init_buffer(struct lettScritt *pc){
  //init_monitor(&pc->m, 2);
  pc->n_lett = 0;
  pc->n_scritt = 0;
}

void leggi (struct lettScritt *pc){
  inizio_lettura(pc);
  printf("Valore letto - %d\n", pc->buffer);
  fine_lettura(pc);
}


void inizio_lettura (struct lettScritt *pc){
  enter_monitor(&pc->m);

  if (pc->n_scritt > 0)
    wait_condition(&pc->m, CV_LETT);

  pc->n_lett++;

  signal_condition(&pc->m, CV_LETT);
  leave_monitor(&pc->m);
}

void fine_lettura (struct lettScritt *pc){
  enter_monitor(&pc->m);

  pc->n_lett--;
  if (pc->n_lett == 0)
    signal_condition (&pc->m, CV_SCRITT);

  leave_monitor(&pc->m);
}

void inizio_scrittura (struct lettScritt *pc){
  srand(getpid()*time(NULL));
  enter_monitor(&pc->m);

  if (pc->n_lett > 0 || pc->n_scritt > 0)
    wait_condition(&pc->m, CV_SCRITT);

  pc->n_scritt++;
}

void fine_scrittura (struct lettScritt *pc){
  enter_monitor(&pc->m);

  pc->n_scritt--;

  if (queue_condition(&pc->m, CV_SCRITT))
    signal_condition(&pc->m,CV_SCRITT);
  else
    signal_condition(&pc->m,CV_LETT);

  leave_monitor(&pc->m);
}


void scrivi (struct lettScritt *pc){
  inizio_scrittura(pc);
  pc->buffer = rand()%90+10;
  printf("Valore scritto - %d\n", pc->buffer);
  fine_scrittura(pc);
}
