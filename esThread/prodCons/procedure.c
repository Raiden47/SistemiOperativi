#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "procedure.h"

void *produttore (void * p){
  struct prodCons * pc = (struct prodCons *) p;
  srand(time(NULL));
  for (int i = 0 ; i < NUM_PROD ; i++){
    produci(pc, rand()%90+10);
  }
  pthread_exit(NULL);
}


void *consumatore (void * c){
  struct prodCons * pc = (struct prodCons *) c;
  for (int i = 0 ; i < NUM_CONS ; i++){
    printf("- Valore consumato [%ld]\n", consuma(pc));
  }
}



void produci (struct prodCons * pc, long msg){
  inizio_produzione(pc);
  sleep(2);
  pc->buffer = msg;
  printf("+ Valore prodotto [%ld]\n", pc->buffer);
  fine_produzione(pc);
}


long consuma (struct prodCons *pc){
  inizio_consumo(pc);
  sleep(2);
  long msg = pc->buffer;
  fine_consumo(pc);
  return msg;
}



void init_buffer (struct prodCons * pc){

  pthread_mutex_init (&pc->mutex, NULL);
  pthread_cond_init (&pc->cv_prod, NULL);
  pthread_cond_init (&pc->cv_cons, NULL);

  pc->prod = 1;
  pc->cons = 0;
}


void remove_buffer (struct prodCons * pc){
  pthread_mutex_destroy(&pc->mutex);
  pthread_cond_destroy(&pc->cv_prod);
  pthread_cond_destroy(&pc->cv_cons);
  free(pc);
}


bool check_state (int var_check){
  if (var_check == 0)
    return true;
  return false;
}



void inizio_produzione (struct prodCons * pc){
  pthread_mutex_lock(&pc->mutex);

  while(check_state(pc->prod))
    pthread_cond_wait(&pc->cv_prod, &pc->mutex);

  pc->prod = 0;
  printf("+ Inizio produzione\n");
}


void fine_produzione (struct prodCons * pc){
  pc->cons = 1;

  pthread_cond_signal(&pc->cv_cons);
  pthread_mutex_unlock(&pc->mutex);

  printf("+ Fine produzione\n");
}


void inizio_consumo (struct prodCons * pc){
  pthread_mutex_lock(&pc->mutex);

  while (check_state(pc->cons))
    pthread_cond_wait(&pc->cv_cons, &pc->mutex);

  pc->cons = 0;
  printf("- Inizio consumo\n");
}


void fine_consumo (struct prodCons * pc){
  pc->prod = 1;

  pthread_cond_signal(&pc->cv_prod);
  pthread_mutex_unlock(&pc->mutex);

  printf("- Fine consumo\n");
}
