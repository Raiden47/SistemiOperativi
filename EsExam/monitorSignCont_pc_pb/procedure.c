#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "procedure.h"

void init_buffer (struct prodCons *pc){
  init_monitor(&pc->m, 2);
  for (int i = 0 ; i < DIM_BUFFER ; i++)
    pc->state[i] = FREE;
  pc->n_full = 0;
  pc->n_free = DIM_BUFFER;
}

void produci (struct prodCons *pc){

  srand(getpid()*time(NULL));

  enter_monitor(&pc->m);

  while (pc->n_full == DIM_BUFFER)
    wait_condition(&pc->m, CV_PROD);

  int pos = check_state(pc, FREE);
  pc->state[pos] = IN_USE;
  pc->n_full += 1;
  sleep(1);

  leave_monitor(&pc->m);

  pc->buffer[pos] = rand()%90+10;
  printf("Valore prodotto - %d\n", pc->buffer[pos]);

  enter_monitor(&pc->m);

  pc->state[pos] = FULL;
  pc->n_free -= 1;
  sleep(1);

  signal_condition(&pc->m, CV_CONS);

  leave_monitor(&pc->m);

}

void consuma (struct prodCons *pc){

  enter_monitor(&pc->m);

  while (pc->n_free == DIM_BUFFER)
    wait_condition(&pc->m, CV_CONS);

  int pos = check_state(pc, FULL);
  pc->state[pos] = IN_USE;
  pc->n_free += 1;
  sleep(1);

  leave_monitor (&pc->m);

  printf("Valore consumato - %d\n", pc->buffer[pos]);

  enter_monitor(&pc->m);

  pc->state[pos] = FREE;
  pc->n_full -= 1;
  sleep(1);

  signal_condition(&pc->m, CV_PROD);

  leave_monitor(&pc->m);

}


int check_state (struct prodCons *pc, int st){
  int i = 0;
  while (i < DIM_BUFFER && pc->state[i] != st)
    i++;
  return i;
}
