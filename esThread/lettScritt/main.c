#include "procedure.h"

int main () {

  pthread_t thread[N_THREAD];

  pthread_attr_t attr;

  struct lettScritt * ls = malloc(sizeof(struct lettScritt));

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  init_buffer(ls);

  for (int i = 0 ; i < N_THREAD ; i++){
    if (i%2)
      pthread_create(&thread[i], &attr, scrittore, (void *)ls);
    else
      pthread_create(&thread[i], &attr, lettore, (void *)ls);
  }

  for (int i = 0 ; i < N_THREAD ; i++)
    pthread_join(&thread[i], NULL);

  pthread_attr_destroy(&attr);
  remove_buffer(ls);

  free(ls);

  pthread_exit(0);
}
