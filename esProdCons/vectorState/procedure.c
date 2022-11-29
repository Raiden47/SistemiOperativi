#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

#include "procedure.h"
#include "semaphore.h"

void change_state(struct prodCons * bff, int state, int pos){
  bff->state[pos]=state;
}

// Da controllare:
// Il produttore non dovrebbe controllare e nel caso NON produrre
void produttore (struct prodCons * bff, int ds_sem){
  int pos = 0;

  wait_sem (ds_sem, SPAZIO_DISPONIBILE);
  wait_sem (ds_sem, MUTEX_P);

  // Controllo lo stato
  while (bff->state[pos] != EMPTY && pos < DIM_BUFFER)
    pos++;

  change_state(bff, IN_USE, pos);
  signal_sem(ds_sem, MUTEX_P);

  sleep(rand()%2+1);
  bff->buffer[pos] = rand()%100;
  printf("<--- [%d] Produttore - Valore prodotto [%d] --->\n",getpid(), bff->buffer[pos]);

  change_state(bff, FULL, pos);
  signal_sem(ds_sem, MESSAGGIO_DISPONIBILE);
}

void consumatore (struct prodCons * bff, int ds_sem){
  int pos = 0;

  wait_sem(ds_sem, MESSAGGIO_DISPONIBILE);
  wait_sem(ds_sem, MUTEX_C);

  while(pos < DIM_BUFFER && bff->state[pos] != FULL)
    pos++;

  change_state(bff, IN_USE, pos);
  signal_sem(ds_sem, MUTEX_C);

  sleep(rand()%2+1);
  printf("<--- [%d] Consumatore - Valore consumato [%d] --->\n", getpid(),bff->buffer[pos]);

  change_state(bff,EMPTY, pos);
  signal_sem(ds_sem, SPAZIO_DISPONIBILE);

}
