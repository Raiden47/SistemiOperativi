#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>

#include "procedure.h"

int main () {

  key_t k_shmem = IPC_PRIVATE;
  int ds_shmem = shmget (k_shmem, sizeof(struct lettScritt *),  IPC_CREAT | 0664);

  struct lettScritt *pc = (struct lettScritt *)shmat(ds_shmem, NULL, 0);

  init_monitor(&pc->m,2);
  init_buffer(pc);

  pid_t pid;

  for (int i = 0 ; i < N_SCRITT ; i++){
    pid = fork();
    if (pid == 0){
      sleep(1);
      scrivi(pc);
      exit(0);
    }
  }
  for (int i = 0 ; i <  N_LETT; i++){
    pid = fork();
    if (pid == 0){
      sleep(1);
      leggi(pc);
      exit(0);
    }
  }

  for (int i = 0 ; i < (N_LETT + N_SCRITT) ; i++)
    wait(NULL);

  remove_monitor(&pc->m);
  shmctl(ds_shmem, IPC_RMID, 0);

  return 0;
}
