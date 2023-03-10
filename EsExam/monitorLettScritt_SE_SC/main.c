#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>

#include "procedure.h"

int main (){

  key_t k_shmem = IPC_PRIVATE;
  int ds_shmem = shmget(k_shmem, sizeof(struct letScr *), IPC_CREAT | 0664);

  struct letScr * ls = (struct letScr *) shmat (ds_shmem, NULL, 0);

  init_buffer(ls);

  pid_t pid;

  for (int i = 0 ; i < N_SCR ; i++){
    pid = fork();
    if (pid == 0){
      sleep(rand()%3);
      scrivi(ls);
      exit(0);
    }
  }
  for (int i = 0 ; i < N_LET ; i++){
    pid = fork();
    if (pid == 0){
      sleep(rand()%3);
      leggi(ls);
      exit(0);
    }
  }

  for (int i = 0 ; i < N_PROC ; i++)
    wait (NULL);

  remove_monitor(&ls->m);
  shmctl(ds_shmem,  IPC_RMID, 0);

  return 0;
}
