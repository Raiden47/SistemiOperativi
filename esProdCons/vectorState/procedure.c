#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

#include "procedure.h"
#include "semaphore.h"

int check_state (struct prodCons * bff){
  int pos = 0;
  while (pos < DIM_BUFFER) {
    if (bff->buffer[pos] == EMPTY)
      return pos;
    pos++;
  }
  return pos;
}

// Da controllare:
// Il produttore non dovrebbe controllare e nel caso NON produrre
void produttore (struct prodCons * bff, int ds_sem){
  int pos;

  srand(getpid()*time(NULL));

  wait_sem (ds_sem, SPAZIO_DISPONIBILE);
  wait_sem (ds_sem, MUTEX_STATE);

  // Controllo lo stato
  pos = check_state (*bff);
  if (pos != DIM_BUFFER)
    bff->buffer[pos] = rand()%100;

  signal_sem(ds_sem, MUTEX_STATE);
  signal_sem(ds_sem, MESSAGGIO_DISPONIBILE):

}

void consumatore (struct prodCons * bff, int ds_sem){

}
