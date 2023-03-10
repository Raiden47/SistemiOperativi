#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "semaphore.h"
#include "procedure.h"


void scrivi (struct lettScritt *ls, int ds_sem){

  srand(getpid() + time(NULL));
  inizio_scrittura (ls, ds_sem);

  sleep(1);
  ls->buffer = num_gen ();
  printf("Valore scritto - %d\n", ls->buffer);
  sleep(1);

  fine_scrittura (ls, ds_sem);

}


void leggi (struct lettScritt *ls, int ds_sem){

  inizio_lettura (ls, ds_sem);

  sleep(1);
  printf("Valore letto - %d\n", ls->buffer);
  sleep(1);

  fine_lettura (ls, ds_sem);
}


void inizio_lettura (struct lettScritt *ls, int ds_sem){
  wait_sem (ds_sem, MUTEX_L);

  ls->n_lett += 1;

  if (ls->n_lett == 1)
    wait_sem (ds_sem, SYNCH);

  signal_sem (ds_sem, MUTEX_L);
}


void fine_lettura (struct lettScritt *ls, int ds_sem){
  wait_sem (ds_sem, MUTEX_L);

  ls->n_lett -= 1;

if (ls->n_lett == 0)
    signal_sem (ds_sem, SYNCH);

  signal_sem (ds_sem, MUTEX_L);
}


void inizio_scrittura (struct lettScritt *ls, int ds_sem){
  wait_sem (ds_sem, SYNCH);
}


void fine_scrittura (struct lettScritt *ls, int ds_sem){
  signal_sem (ds_sem, SYNCH);
}




int num_gen ()
  {return rand()%90+10;}


void init_res (struct lettScritt *ls)
  {ls->n_lett = 0;}
