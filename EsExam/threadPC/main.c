#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "procedure.h"

int main (){
  struct prodCons * pc = malloc(sizeof(struct prodCons));

  pthread_t thread[N_THREAD];

  pthread_attr_t attr;

  init_buffer(pc);

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for (int i = 0 ; i < N_THREAD ; i++){
    if (i%2)
      pthread_create(&thread[i], &attr, Produci, (void *)pc);
    else
      pthread_create(&thread[i], &attr, Consuma, (void *)pc);
  }

  for (int i = 0 ; i < N_THREAD ; i++)
    pthread_join(thread[i], NULL);

  pthread_attr_destroy(&attr);
  remove_buffer(pc);

  pthread_exit(0);
}
