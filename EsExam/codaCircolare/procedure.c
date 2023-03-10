#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "procedure.h"
#include "semaphore.h"

void produci (struct pc_buffer *pc, int ds_sem){

  srand(time(NULL)*getpid());

  wait_sem(ds_sem, SPAZIO_DISPONIBILE);
  wait_sem(ds_sem, MUTEX_P);

  sleep(1);
  pc->buffer[pc->testa] = num_generator();
  printf("Valore prodotto - %d\n", pc->buffer[pc->testa]);
  pc->testa = (pc->testa + 1) % DIM_BUFFER;
  sleep(1);

  signal_sem(ds_sem, MUTEX_P);
  signal_sem(ds_sem, MESSAGGIO_DISPONIBILE);

}


void consuma (struct pc_buffer *pc, int ds_sem){

  wait_sem(ds_sem, MESSAGGIO_DISPONIBILE);
  wait_sem(ds_sem, MUTEX_C);

  sleep(1);
  printf("Valore consumato - %d\n", pc->buffer[pc->coda]);
  pc->coda = (pc->coda + 1) % DIM_BUFFER;
  sleep(1);

  signal_sem(ds_sem, MUTEX_C);
  signal_sem(ds_sem, SPAZIO_DISPONIBILE);
}


void init_buffer(struct pc_buffer *pc){
  pc->testa = 0;
  pc->coda = 0;
}


int num_generator (){
  return rand()%90+10;
}
