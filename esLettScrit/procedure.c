#include <stdio.h>

#include "procedure.h"
#include "semaphore.h"

void lettore (int ds_sem, buffer * bff){
  inizio_lettura(ds_sem, bff);
  sleep(2);
  printf("<--- Lettura del valore --->\n");
  printf("\t|--- [%ld] ---|\n", bff->messaggio);
  printf("<--- Fine della lettura --->\n");
  fine_lettura(ds_sem, bff);
}

void scrittore (int ds_sem, buffer * bff){
  inizio_scrittura(ds_sem);
  sleep(2);
  printf("<--- Scrittura del valore --->\n");
  msg val = rand() %1000+8000;
  bff->messaggio = val;
  printf("\t|--- [%ld] ---|\n", val);
  printf("<--- Fine della scrittura --->\n");
  fine_scrittura(ds_sem);
}

//*************************************************

void inizio_lettura (int ds_sem, buffer * bff){
  wait_sem(ds_sem, MUTEXL);

  bff->num_lettori++;
  if (bff->num_lettori == 1)
    wait_sem(ds_sem, SYNCH);

  signal_sem(ds_sem, MUTEXL);
}

void fine_lettura (int ds_sem, buffer * bff){
  wait_sem(ds_sem, MUTEXL);

  bff->num_lettori--;
  if (bff->num_lettori == 0)
    signal_sem(ds_sem, SYNCH);

  signal_sem(ds_sem, MUTEXL);
}

void inizio_scrittura (int ds_sem){
  wait_sem(ds_sem, SYNCH);
}

void fine_scrittura (int ds_sem){
  signal_sem(ds_sem, SYNCH);
}
