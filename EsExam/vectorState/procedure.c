#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "semaphore.h"
#include "procedure.h"


void produci (int ds_sem, struct pc_buffer *pc){
  srand(getpid()*time(NULL));

  wait_sem(ds_sem, SPAZIO_DISPONIBILE);
  wait_sem(ds_sem, MUTEX_P);

  int pos = search_pos(pc, FREE);
  pc->state[pos] = IN_USE;
  sleep(1);

  signal_sem(ds_sem, MUTEX_P);

  pc->buffer[pos] = num_gen();
  printf("Valore prodotto - %d\n", pc->buffer[pos]);

  wait_sem(ds_sem, MUTEX_P);
  sleep(1);

  pc->state[pos] = FULL;
  signal_sem(ds_sem, MUTEX_P);
  signal_sem(ds_sem, MESSAGGIO_DISPONIBILE);
}


void consuma (int ds_sem, struct pc_buffer *pc){

  wait_sem(ds_sem, MESSAGGIO_DISPONIBILE);
  wait_sem(ds_sem, MUTEX_C);

  int pos = search_pos(pc, FULL);
  pc->state[pos] = IN_USE;
  sleep(1);

  signal_sem(ds_sem, MUTEX_C);

  printf("Valore consumato - %d\n", pc->buffer[pos]);

  wait_sem(ds_sem, MUTEX_C);
  sleep(1);

  pc->state[pos] = FREE;
  signal_sem(ds_sem, MUTEX_C);
  signal_sem(ds_sem, SPAZIO_DISPONIBILE);

}



int num_gen(){
  return rand () % 90 + 10;
}


void init_buffer (struct pc_buffer *pc){
  for (int i = 0 ; i < DIM_BUFFER ; i++)
    pc->state[i] = FREE;
}



int search_pos (struct pc_buffer *pc, int st){
  for (int i = 0 ; i < DIM_BUFFER ; i++)
    if (pc->state[i] == st)
      return i;
  return 0;
}
