#include <stdio.h>
#include <unistd.h>

#include <sys/wait.h>

#include "semaphore.h"
#include "procedure.h"

int main () {

  key_t k_shmem = IPC_PRIVATE;
  key_t k_sem = IPC_PRIVATE;

  int ds_shmem = shmget (k_shmem, sizeof(struct lettScritt *), IPC_CREAT | 0664);
  int ds_sem = semget (k_sem, 4, IPC_CREAT | 0664);

  struct lettScritt *ls = shmat (ds_shmem, NULL, 0);
  semctl (ds_sem, MUTEX_L, SETVAL, 1);
  semctl (ds_sem, MUTEX_S, SETVAL, 1);
  semctl (ds_sem, MUTEX, SETVAL, 1);
  semctl (ds_sem, SYNCH, SETVAL, 1);

  init_resources(ls);

  pid_t pid;

  for (int i = 0 ; i < N_SCRITT ; i++){
    pid = fork();
    if (pid == 0){
      scrivi (ls, ds_sem);
      exit(0);
    }
  }

  for (int i = 0 ; i < N_LETT ; i++){
    pid = fork();
    if (pid == 0){
      leggi (ls, ds_sem);
      exit(0);
    }
  }

  for (int i = 0 ; i < (N_LETT + N_SCRITT) ; i++)
    wait(NULL);

  shmctl (ds_shmem, IPC_RMID, 0);
  semctl (ds_sem, 4, IPC_RMID);

  return 0;
}
