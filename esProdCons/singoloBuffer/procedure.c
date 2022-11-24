#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "procedure.h"
#include "semaphore.h"

void produttore (int *shm_buffer, int ds_sem){
  wait_sem(ds_sem, SPAZIO_DISPONIBILE);
  sleep(2);
  *shm_buffer = rand () % 100;
  printf("<--- Valore prodotto [%d] --->\n", *shm_buffer);
  signal_sem(ds_sem, MESSAGGIO_DISPONIBILE);
}

void consumatore (int *shm_buffer, int ds_sem){
  wait_sem(ds_sem, MESSAGGIO_DISPONIBILE);
  sleep(2);
  printf("<--- Consumo il valore [%d] --->\n", *shm_buffer);
  signal_sem(ds_sem,SPAZIO_DISPONIBILE);
}
