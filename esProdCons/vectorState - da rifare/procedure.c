#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

#include "procedure.h"
#include "semaphore.h"

int check_state (struct prodCons * bff, int state){
  int pos = 0;
  while (pos < DIM_BUFFER) {
    if (bff->buffer[pos] == state)
      return pos;
    pos++;
  }
  return pos;
}

void change_state(struct prodCons * bff, int state, int pos){
  bff->vector[pos]=state;
}

// Da controllare:
// Il produttore non dovrebbe controllare e nel caso NON produrre
void produttore (struct prodCons * bff, int ds_sem){
  int pos;

  srand(getpid()*time(NULL));

  wait_sem (ds_sem, SPAZIO_DISPONIBILE);
  wait_sem (ds_sem, MUTEX_STATE);

  // Controllo lo stato
  pos = check_state (bff,EMPTY);

  change_state(bff, IN_USE, pos);
  sleep(rand()%5+1);

  // if (pos != DIM_BUFFER)
    bff->buffer[pos] = rand()%100;
  printf("<--- [%d] Produttore - Valore prodotto [%d] --->\n",getpid(), bff->buffer[pos]);

  change_state(bff, FULL, pos);

  signal_sem(ds_sem, MUTEX_STATE);
  signal_sem(ds_sem, MESSAGGIO_DISPONIBILE);

}

void consumatore (struct prodCons * bff, int ds_sem){
  int pos = 0;

  wait_sem(ds_sem, MESSAGGIO_DISPONIBILE);
  wait_sem(ds_sem, MUTEX_STATE);

  pos = check_state(bff, FULL);
  change_state(bff, IN_USE, pos);

  sleep(rand()%5+1);
  printf("<--- [%d] Consumatore - Valore consumato [%d] --->\n", getpid(),bff->buffer[pos]);

  change_state(bff,EMPTY, pos);
  signal_sem(ds_sem, MUTEX_STATE);
  signal_sem(ds_sem, SPAZIO_DISPONIBILE);

}
