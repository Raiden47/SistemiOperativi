#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "procedure.h"

void init_buffer (struct lettScritt * ls){
  ls->n_scritt = 0;
  ls->n_lett = 0;
}

// Da controllare meglio...
void leggi (struct lettScritt * ls){
  enter_monitor(&ls->m);
  printf("Lettore [%d] - Entro nel monitor\n", getpid());

  while (ls->n_scritt > 0)
    wait_condition(&ls->m, CV_LTT);

  ls->n_lett++;
  leave_monitor(&ls->m);

  sleep(rand()%3+1);
  printf("Lettore [%d] - Valore letto [%d]\n", getpid(), ls->buffer);

  enter_monitor(&ls->m);
  ls->n_lett--;

  if (ls->n_lett == 0)
    signal_condition(&ls->m, CV_SCR);
  leave_monitor(&ls->m);
}


void scrivi (struct lettScritt * ls){
  enter_monitor(&ls->m);
  printf("Scrittore [%d] - Entrato nel monitor\n", getpid());

  while(ls->n_lett > 0 || ls->n_scritt)
    wait_condition(&ls->m, CV_SCR);

  ls->n_scritt++;
  leave_monitor(&ls->m);

  sleep(rand()%3+1);

  ls->buffer = rand()%90+10;
  printf("Scrittore [%d] - Valore scritto [%d]\n", getpid(), ls->buffer);

  enter_monitor(&ls->m);
  ls->n_scritt--;
  if(queue_condition(&ls->m,CV_SCR))
    signal_condition(&ls->m,CV_SCR);
  else
    signal_all(&ls->m,CV_LTT);
  leave_monitor(&ls->m);
}
