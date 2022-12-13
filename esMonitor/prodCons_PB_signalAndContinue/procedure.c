#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "procedure.h"

void init_buffer(struct prodCons * pc){
  for (int i = 0 ; i < DIM_BUFFER ; i++)
    pc->state[i] = FREE;
  pc->num_free = DIM_BUFFER;
  pc->num_full = 0;
}


int check_state (struct prodCons * pc, int st){
  int i = 0;
  while (i < DIM_BUFFER && pc->state[i] != st)
    i++;
  return i;
}


void produttore (struct prodCons * pc, int value){
  enter_monitor(&pc->m);
  printf("Produttore [%d] - Sono entrato nel monitor\n", getpid());

  while (pc->num_free == 0)
    wait_condition(&pc->m, CV_PROD);

  int pos = check_state(pc, FREE);

  // int pos = 0;
  // while (pos < DIM_BUFFER || pc->state[pos] != FREE)
  //   pos++;

  pc->state[pos] = IN_USE;
  pc->num_free -= 1;

  printf("-------%d------\n", pos);

  leave_monitor(&pc->m);

  pc->buffer[pos] = value;
  printf("Produttore [%d] - Ho prodotto [%d]\n", getpid(), value);

  enter_monitor(&pc->m);

  pc->state[pos] = FULL;
  pc->num_full += 1;

  sleep(rand()%3+1);

  signal_condition(&pc->m, CV_CONS);
  leave_monitor(&pc->m);

  printf("Produttore [%d] - Produzione terminata\n", getpid());
}


void consumatore (struct prodCons * pc){
  enter_monitor(&pc->m);
  printf("Consumatore [%d] - Sono entrato nel monitor\n", getpid());

  while (pc->num_full == 0)
    wait_condition(&pc->m,CV_CONS);

  int pos = check_state(pc, FULL);

  // int pos = 0;
  // while (pos < DIM_BUFFER || pc->state[pos] != FULL)
  //   pos++;

  pc->state[pos] = IN_USE;
  pc->num_full -= 1;

  leave_monitor(&pc->m);

  printf("Consumatore [%d] - Ho consumato [%d]\n", getpid(), pc->buffer[pos]);

  enter_monitor(&pc->m);

  pc->state[pos] = FREE;
  pc->num_free += 1;

  sleep(rand()%3+1);

  signal_condition(&pc->m,CV_PROD);
  leave_monitor(&pc->m);

  printf("Consumatore [%d] - Consumo terminato\n", getpid());
}
