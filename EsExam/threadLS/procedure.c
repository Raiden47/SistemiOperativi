#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "procedure.h"

void *Lettore (void *l){
  srand(time(NULL));
  struct letScr *ls = (struct letScr *)l;
  for (int i = 0 ; i < N_LET ; i++){
    sleep(rand()%3+1);
    leggi(ls);
  }
  pthread_exit(0);
}

void *Scrittore (void *s){
  srand(time(NULL));
  struct letScr *ls = (struct letScr *)s;
  for (int i = 0 ; i < N_SCR ; i++){
    sleep(rand()%3+1);
    scrivi(ls);
  }
  pthread_exit(0);
}


void leggi (struct letScr *ls){
  inizio_lettura(ls);
  sleep(rand()%3+1);
  printf("Valore letto - %d\n", ls->buffer);
  fine_lettura(ls);
}

void scrivi (struct letScr *ls){
  inizio_scrittura(ls);
  sleep(rand()%3+1);
  ls->buffer = rand()%90+10;
  printf("Valore Scritto - %d\n", ls->buffer);
  fine_scrittura(ls);
}


void inizio_lettura (struct letScr *ls){
  pthread_mutex_lock(&ls->mutex);

  while (ls->num_scr > 0)
    pthread_cond_wait(&ls->cv_let, &ls->mutex);

  ls->num_let++;
  pthread_mutex_unlock(&ls->mutex);
}

void fine_lettura (struct letScr *ls){
  pthread_mutex_lock(&ls->mutex);

  ls->num_let--;
  if (ls->num_let == 0)
    pthread_cond_signal(&ls->cv_scr);

  pthread_cond_signal(&ls->cv_let);
  pthread_mutex_unlock(&ls->mutex);
}

void inizio_scrittura (struct letScr *ls){
  pthread_mutex_lock(&ls->mutex);

  ls->scr_queue++;

  while (ls->num_let > 0 || ls->num_scr > 0)
    pthread_cond_wait(&ls->cv_scr, &ls->mutex);

  ls->num_scr++;
}

void fine_scrittura (struct letScr *ls){
  ls->num_scr--;
  ls->scr_queue--;
  if (ls->scr_queue > 0)
    pthread_cond_signal(&ls->cv_scr);
  else
    pthread_cond_broadcast(&ls->cv_let);

  pthread_mutex_unlock(&ls->mutex);
}


void init_buffer (struct letScr *ls){
  pthread_mutex_init (&ls->mutex,NULL);
  pthread_cond_init (&ls->cv_scr,NULL);
  pthread_cond_init (&ls->cv_let,NULL);

  ls->num_let = 0;
  ls->num_scr = 0;
  ls->scr_queue = 0;
}

void remove_buffer (struct letScr *ls){
  pthread_mutex_destroy (&ls->mutex);
  pthread_cond_destroy (&ls->cv_let);
  pthread_cond_destroy (&ls->cv_scr);
}
