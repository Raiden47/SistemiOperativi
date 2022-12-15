#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "procedure.h"

int main () {

  struct prodCons * pc = malloc(sizeof(struct prodCons));;

  pthread_t thread[N_THREADS];

  pthread_attr_t attr;

  init_buffer(pc);

  pthread_attr_init (&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for (int i = 0 ; i < N_THREADS ; i++){
    if (i%2)
      pthread_create(&thread[i], &attr, produttore, (void *)pc);
    else
      pthread_create(&thread[i], &attr, consumatore, (void *)pc);
  }

  for (int i = 0 ; i < N_THREADS ; i++)
    pthread_join(thread[i],NULL);

  pthread_attr_destroy(&attr);
  remove_buffer(pc);

  pthread_exit(0);
}
