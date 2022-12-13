#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "procedure.h"

int main () {

  pid_t pid;
  key_t k_shmem = IPC_PRIVATE;
  int ds_shmem = shmget(k_shmem, sizeof(struct lettScritt *), IPC_CREAT | 0664);
  struct lettScritt * ls = shmat (ds_shmem, NULL, 0);

  init_monitor(&ls->m, 2);
  init_buffer(ls);

  for (int i = 0 ; i < N_LTT ; i++){
    pid = fork();
    if (pid == 0){
      srand(getpid()*time(NULL));
      leggi(ls);
      exit(0);
    }
  }

  for (int i = 0 ; i < N_SCR ; i++){
    pid = fork();
    if (pid == 0){
      srand(getpid()*time(NULL));
      scrivi(ls);
      exit(0);
    }
  }

  for (int i = 0 ; i < N_SCR + N_LTT ; i++)
    wait (NULL);

  remove_monitor(&ls->m);
  shmctl(ds_shmem,IPC_RMID, 0);
  return 0;
}
