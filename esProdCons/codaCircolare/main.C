#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>

include "procedure.h"

int main () {

  key_t k_shmem = IPC_PRIVATE;
  key_t k_sem = IPC_PRIVATE;

  int ds_shmem = shmget (k_shmem, sizeof(int), IPC_CREAT | 0664);

  if (ds_shmem < 0) {perror("Errore SHMGET"); _exit(1);}

  struct prodcons *pc ;
  pc = (struct prodCons *) shmat(ds_shmem, NULL, 0);

  *p->testa = 0;
  *p->coda = 0;

  int ds_sem = semget (k_sem, 4, IPC_CREAT | 0664);
  if (ds_sem < 0) {perror("Errore SEMGET"); _exit(1);}



}
