#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>

#include "procedure.h"

int main (){

  key_t k_shmem = IPC_PRIVATE;
  int ds_shmem = shmget (k_shmem, sizeof(struct prodCons *), IPC_CREAT | 0664);

  struct prodCons *pc = (struct prodCons *)shmat(ds_shmem, NULL, 0);

  init_buffer(pc);

  pid_t pid;

  for (int i = 0 ; i < N_PROD ; i++){
    pid = fork();
    if (pid == 0){
      produci(pc);
      exit(0);
    }
  }

  for (int i = 0 ; i < N_CONS ; i++){
    pid = fork();
    if (pid == 0){
      consuma(pc);
      exit(0);
    }
  }

  for (int i = 0 ; i < (N_PROD + N_CONS) ; i++)
    wait (NULL);

  remove_monitor(&pc->m);
  shmctl(ds_shmem, IPC_RMID, 0);

  return 0;
}
