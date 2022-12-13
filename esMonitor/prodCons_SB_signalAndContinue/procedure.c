#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "procedure.h"


void init_buffer(struct prodCons * pc){
  pc->prod = K_PC;
  pc->cons = W_PC;
}

void abilita_prod_cons (struct prodCons * pc, int ds_prod, int ds_cons){
  pc->prod = ds_prod;
  pc->cons = ds_cons;
}


void produttore (struct prodCons * pc){
  enter_monitor(&pc->m);
  printf("Produttore [%d] - Sono entrato nel monitor \n", getpid());

  sleep(1);

  while (pc->prod == 0)
    wait_condition(&pc->m, CV_PROD);

  sleep(2);

  int tmp = rand()%90+10;
  pc->buffer = tmp;
  printf("Produttore [%d] - Valore prodotto [%d] \n", getpid(), pc->buffer);

  abilita_prod_cons(pc, W_PC, K_PC);

  signal_condition(&pc->m, CV_CONS);
  leave_monitor(&pc->m);
  printf("Produttore [%d] - Sono uscito nel monitor \n", getpid());
}


void consumatore (struct prodCons * pc){
  enter_monitor(&pc->m);
  printf("Consumatore [%d] - Sono entrato nel monitor \n", getpid());

  sleep(1);

  while (pc->cons == 0)
    wait_condition(&pc->m, CV_CONS);

  sleep(2);

  printf("Consumatore [%d] - Valore consumato [%d] \n", getpid(), pc->buffer);

  abilita_prod_cons(pc, K_PC, W_PC);

  signal_condition(&pc->m, CV_PROD);

  leave_monitor(&pc->m);
  printf("Consumatore [%d] - Sono uscito nel monitor \n", getpid());
}
