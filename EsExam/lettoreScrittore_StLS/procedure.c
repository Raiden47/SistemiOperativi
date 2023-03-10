#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "semaphore.h"
#include "procedure.h"

void leggi (struct lettScritt *ls, int ds_sem){
  inizio_lettura(ls, ds_sem);

  sleep(1);
  printf("Valore letto - %d\n", ls->buffer);
  sleep(1);

  fine_lettura(ls, ds_sem);
}

void scrivi (struct lettScritt *ls, int ds_sem){
  srand(getpid()+time(NULL));
  inizio_scrittura(ls, ds_sem);

  sleep(1);
  ls->buffer = num_gen();
  printf("Valore scritto - %d\n", ls->buffer);
  sleep(1);

  fine_scrittura(ls, ds_sem);
}



void inizio_lettura (struct lettScritt *ls, int ds_sem){
  wait_sem (ds_sem, MUTEX_L);

  ls->n_lett += 1;

  if (ls->n_lett == 1)
    wait_sem(ds_sem, SYNCH);
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
  wait_sem (ds_sem, MUTEX_S);

  ls->n_scritt += 1;

  if (ls->n_scritt == 1)
    wait_sem (ds_sem, SYNCH);

  signal_sem (ds_sem, MUTEX_S);
  wait_sem (ds_sem, MUTEX);

}

void fine_scrittura (struct lettScritt *ls, int ds_sem){
  signal_sem (ds_sem, MUTEX);
  wait_sem (ds_sem, MUTEX_S);

  ls->n_scritt -= 1;

  if (ls->n_scritt == 0)
    signal_sem (ds_sem, SYNCH);

  signal_sem (ds_sem, MUTEX_S);
}


int num_gen()
  {return rand()%90+10;}
void init_resources (struct lettScritt *ls)
  {ls->n_lett=0;ls->n_scritt=0;}
