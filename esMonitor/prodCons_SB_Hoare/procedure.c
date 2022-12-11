#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>

#include "procedure.h"

void produzione (struct prodCons * pc, int valore){

  printf("Produttore:\n");

  enter_monitor(&pc->m);
  printf("... Entro nel monitor\n");

  if (pc->buffer_occupato == 1){
    printf("... Monitor occupato\n");
    wait_condition(&pc->m, CV_PROD);
  }

  pc->buffer = valore;
  pc->buffer_libero = 0;
  pc->buffer_occupato = 1;

  printf("...Valore prodotto [%d]\n", pc->buffer);
  signal_condition(&pc->m, CV_CONS);

  printf("... Lascio il monitor\n");
  leave_monitor(&pc->m);

}

void consumazione (struct prodCons * pc){

  printf("Consumatore:\n");

  enter_monitor(&pc->m);
  printf("... Entro nel monitor\n");

  if (pc->buffer_libero == 1){
    printf("... Monitor occupato\n");
    wait_condition(&pc->m, CV_CONS);
  }

  pc->buffer_libero = 1;
  pc->buffer_occupato = 0;
  printf("... Valore consumato [%d]\n", pc->buffer);
  signal_condition(&pc->m, CV_PROD);

  printf("... Lascio il monitor\n");
  leave_monitor(&pc->m);

}
