#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>

#include "procedure.h"

int main () {

  key_t k_shmem = IPC_PRIVATE;

  int ds_shmem = shmget(k_shmem, sizeof(struct prodcons *), IPC_CREAT | 0664);

  struct prodcons *pc = (struct prodcons *)shmat(ds_shmem, NULL , 0);

  init_monitor(&pc->m,2);

  for (int i = 0 ; i < DIM_BUFFER ; i++)
    pc->state[i] = FREE;
  pc->num_free = DIM_BUFFER;
  pc->num_full = 0;

  pid_t pid;
  for (int i = 0 ; i < DIM_PROD ; i++){
    pid = fork();
    if (pid == 0){
      produci(pc);
      exit(0);
    }
  }

  for (int i = 0 ; i < DIM_CONS ; i++){
    pid = fork();
    if (pid == 0){
      consuma(pc);
      exit(0);
    }
  }

  for (int i = 0 ; i < (DIM_CONS + DIM_PROD) ; i++)
    wait(NULL);

  remove_monitor(&pc->m);
  shmctl(ds_shmem, IPC_RMID, 0);

  return 0;
}
