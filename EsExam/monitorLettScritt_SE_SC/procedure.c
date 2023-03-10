#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "procedure.h"

void leggi (struct letScr *ls){
  inizio_lettura(ls);
  sleep(1);
  printf("Valore letto - %d \n", ls->buffer);
  fine_lettura(ls);
}

void scrivi (struct letScr *ls){
  inizio_scrittura(ls);
  sleep(1);
  ls->buffer = rand()%90+10;
  printf("Valore scritto - %d\n", ls->buffer);
  fine_scrittura(ls);
}


void inizio_lettura (struct letScr *ls){
  enter_monitor(&ls->m);

  while (ls->n_scr > 0)
    wait_condition(&ls->m, CV_L);

  ls->n_let++;
  leave_monitor(&ls->m);
}

void fine_lettura (struct letScr *ls){
  enter_monitor(&ls->m);

  ls->n_let--;
  if (ls->n_let == 0)
    signal_condition(&ls->m, CV_S);

  leave_monitor(&ls->m);
}

void inizio_scrittura (struct letScr *ls){
  srand(getpid()*time(NULL));
  enter_monitor(&ls->m);

  while (ls->n_let > 0 || ls->n_scr > 0)
    wait_condition(&ls->m, CV_S);

    ls->n_scr++;
}

void fine_scrittura (struct letScr *ls){

  ls->n_scr--;
  if (queue_condition(&ls->m, CV_S))
    signal_condition(&ls->m, CV_S);
  else
    signal_all(&ls->m, CV_L);

  leave_monitor(&ls->m);
}


void init_buffer (struct letScr *ls){
  init_monitor(&ls->m, 2);
  ls->n_let = 0;
  ls->n_scr = 0;
}
