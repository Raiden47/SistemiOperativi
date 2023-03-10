#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "procedure.h"

int main () {

  pthread_t thread[N_THREAD];

  pthread_attr_t attr;
  pthread_attr_init(&attr);

  struct letScr *ls = malloc(sizeof(struct letScr));

  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for (int i = 0 ; i < N_THREAD ; i++){
    if (i%2==0)
      pthread_create(&thread[i], &attr, Scrittore, (void *)ls);
    else
      pthread_create(&thread[i], &attr, Lettore, (void *)ls);
  }

  for (int i = 0 ; i < N_THREAD ; i++)
    pthread_join(thread[i], NULL);

  pthread_attr_destroy(&attr);
  remove_buffer(ls);

  pthread_exit(0);
}
