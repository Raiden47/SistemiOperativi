#include <time.h>

#include "procedure.h"

void init_buffer (struct lettScritt * ls){
  pthread_mutex_init(&ls->mutex, NULL);
  pthread_cond_init(&ls->cv_scritt, NULL);
  pthread_cond_init(&ls->cv_lett, NULL);

  ls->num_scritt = 0;
  ls->num_lett = 0;
  ls->n_w_s = 0;
  ls->n_w_l = 0;
}


void remove_buffer (struct lettScritt * ls){
  pthread_mutex_destroy(&ls->mutex);
  pthread_cond_destroy(&ls->cv_scritt);
  pthread_cond_destroy(&ls->cv_lett);
}



long leggi (struct lettScritt * ls){
  inizio_lettura(ls);
  sleep(2);
  int val = ls->buffer;
  fine_lettura(ls);
  return val;
}


void scrivi (struct lettScritt * ls, long msg){
  inizio_scrittura(ls);
  sleep(2);
  ls->buffer = msg;
  printf("<- Scritto [%ld] ->\n", ls->buffer);
  fine_scrittura(ls);
}



void inizio_lettura (struct lettScritt * ls){ //Tecnicamente nulla garantisce che il lock venga effettuato in mutua esclusione tra i lettori
                                                        // - forse ho bisogno di una variabile per sincronizzare l'accesso al mutex
  pthread_mutex_lock(&ls->mutex);

  while(ls->num_scritt > 0){
    ls->n_w_l++;
    pthread_cond_wait(&ls->cv_lett, &ls->mutex);
    ls->n_w_l--;
  }

  ls->num_lett++;

  pthread_mutex_unlock(&ls->mutex);
  printf("|- Inizio lettura -|\n");
}


void fine_lettura (struct lettScritt * ls){
  pthread_mutex_lock(&ls->mutex);

  ls->num_lett--;

  // pthread_cond_signal(&ls->cv_lett);
  if (ls->num_lett == 0)
    pthread_cond_signal(&ls->cv_scritt);
  pthread_mutex_unlock(&ls->mutex);
  printf("|- Fine lettura -|\n");
}


void inizio_scrittura (struct lettScritt * ls){
  pthread_mutex_lock(&ls->mutex);
  while (ls->num_lett > 0 || ls->num_scritt > 0){
    ls->n_w_s++;
    pthread_cond_wait(&ls->cv_scritt, &ls->mutex);
    ls->n_w_s--;
  }
  ls->num_scritt++;

  pthread_mutex_unlock(&ls->mutex);
  printf("<- Inizio scrittura ->\n");
}


void fine_scrittura (struct lettScritt * ls){
  pthread_mutex_lock(&ls->mutex);

  ls->num_scritt--;

  if (ls->n_w_s > 1)
    pthread_cond_signal(&ls->cv_scritt);
  else
    pthread_cond_broadcast(&ls->cv_lett);
  pthread_mutex_unlock(&ls->mutex);
}



void *lettore (void * l){
  struct lettScritt * ls = (struct lettScritt *)l;
  for (int i = 0 ; i < N_LETT ; i++){
    printf("|- Letto [%ld] -|\n", leggi(ls));
    sleep(1);
  }
  pthread_exit(NULL);
}


void *scrittore (void * s){
  struct lettScritt * ls = (struct lettScritt *)s;
  srand(time(NULL));
  for (int i = 0 ; i < N_SCRITT ; i++){
    scrivi(ls, (long)rand()%90+10);
    sleep(1);
  }
  pthread_exit(NULL);
}
