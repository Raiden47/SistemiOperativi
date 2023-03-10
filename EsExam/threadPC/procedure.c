#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "procedure.h"

void *Produci (void *p){
  srand(time(NULL));
  struct prodCons *pc = (struct prodCons *)p;
  for (int i = 0 ; i < N_PROD ; i++){
    sleep(rand()%3+1);
    produzione(pc);
  }
  pthread_exit(0);
}
void *Consuma (void *c){
  srand(time(NULL));
  struct prodCons *pc = (struct prodCons *)c;
  for (int i = 0 ; i < N_CONS ; i++){
    sleep(rand()%3+1);
    consumo(pc);
  }
  pthread_exit(0);
}

void produzione (struct prodCons *pc){
  inizio_produzione(pc);
  sleep(rand()%3+1);
  pc->buffer = rand()%90+10;
  printf("Valore prodotto - %ld\n", pc->buffer);
  fine_produzione(pc);
}

void consumo (struct prodCons *pc){
  inizio_consumo(pc);
  sleep(rand()%3+1);
  printf("Valore consumato - %ld\n", pc->buffer);
  fine_consumo(pc);
}

void inizio_produzione (struct prodCons *pc){
  pthread_mutex_lock(&pc->mutex);

  while (pc->prod == 0)
    pthread_cond_wait(&pc->cv_prod, &pc->mutex);

  pc->prod = 0;
}

void fine_produzione (struct prodCons *pc){
  pc->cons = 1;

  pthread_cond_signal(&pc->cv_cons);
  pthread_mutex_unlock(&pc->mutex);
}

void inizio_consumo (struct prodCons *pc){
  pthread_mutex_lock(&pc->mutex);

  while (pc->cons == 0)
    pthread_cond_wait(&pc->cv_cons, &pc->mutex);

  pc->cons = 0;
}

void fine_consumo (struct prodCons *pc){
  pc->prod = 1;

  pthread_cond_signal(&pc->cv_prod);
  pthread_mutex_unlock(&pc->mutex);
}

void init_buffer (struct prodCons *pc){
  pthread_mutex_init(&pc->mutex, NULL);
  pthread_cond_init(&pc->cv_prod, NULL);
  pthread_cond_init(&pc->cv_cons, NULL);

  pc->cons = 0;
  pc->prod = 1;
}


void remove_buffer (struct prodCons *pc){
  pthread_cond_destroy(&pc->cv_prod);
  pthread_cond_destroy(&pc->cv_cons);
  pthread_mutex_destroy(&pc->mutex);
}
