#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "procedure.h"

int * tot = 0;

void *calc_part(void * v){
  int res = 0;

  struct t_par * pt = (struct t_par *) v;

  printf("Inizio a fare oprazioni \n" );
  for (int i = 0 ; i < DIM ; i++){
    // res += pt->vett->v1[pt->index] * pt->vett->v2[i];
    res += pt->v1[pt->index] * pt->v2[i];
  }
  printf("Ho eseguito l'operazione con risultato %d\n", res );
  pthread_mutex_lock (&pt->mutex);

  while (pt->t_sync != 0)
    pthread_cond_wait (&pt->cv_calc, &pt->mutex);

  pt->t_sync++;
  *tot += res;

  pthread_cond_signal (&pt->cv_calc);
  pthread_mutex_unlock (&pt->mutex);

  pt->t_sync--;
  // return res;
  printf("Ho finito le operazioni\n" );
  pthread_exit(NULL);
}

int main () {

  pthread_t thread[NUM_THR];
  struct t_par * pt = malloc(sizeof(struct t_par *)*16);
  // pt->vett = (struct vectors * ) malloc(sizeof(struct vectors *)*10);
  printf("Ho allocato le variabili\n");
  init_buffer(pt);

  pthread_attr_t attr;
  pthread_attr_init (&attr);
  pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE);

  pthread_mutex_init(&pt->mutex, NULL);
  pthread_cond_init(&pt->cv_calc, NULL);
  printf("Ho settato i parametri dei thread\n");

  for (int i = 0 ; i < NUM_THR ; i++){
    printf("Thread %d\n", i);
    pt->index = i;
    pthread_create(&thread[i],&attr,calc_part,(void *)pt);
  }

  printf("Thread istanziati\n");
  for (int i = 0 ; i < NUM_THR ; i++){
    printf("Thread %d terminato\n", i);
    pthread_join(thread[i],NULL);
  }

  printf("Thread terminati\n" );
  printf("Il risultato dell'operazione e' -> %ls\n", tot);

  // free(pt->vett);
  pthread_attr_destroy(&attr);
  pthread_cond_destroy(&pt->cv_calc);
  pthread_mutex_destroy(&pt->mutex);
  free(pt);

  return 0;
}
