#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <sys/shm.h>

#include "semaphore.h"
#include "procedure.h"

int main(){

  int k_shmem = IPC_PRIVATE;
  int k_sem = IPC_PRIVATE;

  int ds_shm = shmget(k_shmem, sizeof(int), IPC_CREAT | 0664);
  int ds_sem = semget(k_sem, 2, IPC_CREAT | 0664);

  int *shmmem = (int *)shmat(ds_shm, NULL, 0);

  semctl(ds_sem, PRODUCI, SETVAL, 1);
  semctl(ds_sem, CONSUMA, SETVAL, 0);

  pid_t pid;

  for (int i = 0 ; i < N_PROC ; i++){
    pid = fork();

    if (pid == 0 && i == 0){
      srand(time(NULL));
      printf("<--- PROD INIT --->\n");
      for (int j = 0 ; j < N_OP ; j++){
        consuma(shmmem, ds_sem);
      }
      exit(0);
    }
    else if (pid == 0 && i == 1){
      srand(time(NULL));
      printf("<--- CONS INIT --->\n");
      for (int j = 0 ; j < N_OP ; j++){
        produci(shmmem, ds_sem);
      }
      exit(0);
    }
  }

  for (int i = 0 ; i < N_PROC ; i++)
    wait(NULL);

  shmctl (ds_shm, IPC_RMID, 0);
  semctl (ds_sem, 2, IPC_RMID);

  return 0;
}
