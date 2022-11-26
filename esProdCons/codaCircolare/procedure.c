#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "procedure.h"
#include "semaphore.h"

void produttore (struct prodcons *p, int ds_sem){
  wait_sem(ds_sem, SPAZIO_DISPONIBILE);
  wait_sem(ds_sem, MUTEX_P);

  sleep(2);

  p->buffer[p->testa] = rand() % 100;
  printf("<--- Valore prodotto [%d] --->\n", p->buffer[p->testa]);
  p->testa = (p->testa + 1) % DIM_BUFFER;

  signal_sem(ds_sem, MUTEX_P);
  signal_sem(ds_sem, MESSAGGIO_DISPONIBILE);
}

void consumatore (struct prodcons *p, int ds_sem){
  wait_sem(ds_sem, MESSAGGIO_DISPONIBILE);
  wait_sem(ds_sem, MUTEX_C);

  sleep(2);

  printf("<--- Valore consumato [%d] --->\n", p->buffer[p->coda]);
  p->coda = (p->coda + 1) % DIM_BUFFER;

  signal_sem(ds_sem, MUTEX_C);
  signal_sem(ds_sem, SPAZIO_DISPONIBILE);
}
