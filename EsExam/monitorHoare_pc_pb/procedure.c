#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "procedure.h"

void produci (struct prodcons *pc){

  srand(getpid()*time(NULL));

  //Entrare nel monitor
  enter_monitor(&pc->m);

  //Check condition
  if (pc->num_full == DIM_BUFFER)
    wait_condition(&pc->m, CV_PROD);

  sleep(1);
  //Modificare lo stato
  int pos = check_state (pc, FREE);
  pc->state[pos] = IN_USE;
  pc->num_free -= 1;

  //rilasciare il monitor
  leave_monitor(&pc->m);

  //Modificare il valore del buffer
  pc->buffer[pos] = rand() % 90 + 10;
  printf("Valore prodotto - [%d]\n", pc->buffer[pos]);

  //Richiedere nuovamente il lock
  enter_monitor(&pc->m);

  sleep(1);
  //cambiare condition
  pc->state[pos] = FULL;
  pc->num_full += 1;
  signal_condition(&pc->m, CV_CONS);

  //uscire dal monitor
  leave_monitor(&pc->m);
}

void consuma (struct prodcons *pc){

  enter_monitor (&pc->m);

  if (pc->num_free == DIM_BUFFER)
    wait_condition(&pc->m, CV_CONS);

  sleep(1);
  int pos = check_state (pc, FULL);
  pc->state[pos] = IN_USE;
  pc->num_full -= 1;  

  leave_monitor(&pc->m);

  printf("Valore consumato - [%d]\n", pc->buffer[pos]);

  enter_monitor(&pc->m);

  sleep(1);
  pc->state[pos] = FREE;
  pc->num_free += 1;

  signal_condition(&pc->m, CV_PROD);

  leave_monitor(&pc->m);
}


int check_state (struct prodcons *pc, int st){
  int i = 0;
  while (i < DIM_BUFFER && pc->state[i] != st)
    i += 1;
  return i;
}
