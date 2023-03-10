#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>

#include "procedure.h"
#include "semaphore.h"

int main (){

  key_t k_shmem = IPC_PRIVATE;
  key_t k_sem = IPC_PRIVATE;

  int ds_shmem = shmget(k_shmem, sizeof(struct pc_buffer *), IPC_CREAT | 0664);
  int ds_sem = semget(k_sem, 4, IPC_CREAT | 0664);

  struct pc_buffer *pc = shmat(ds_shmem, NULL, 0);
  semctl(ds_sem, SPAZIO_DISPONIBILE, SETVAL, DIM_BUFFER);
  semctl(ds_sem, MESSAGGIO_DISPONIBILE, SETVAL, 0);
  semctl(ds_sem, MUTEX_P, SETVAL, 1);
  semctl(ds_sem, MUTEX_C, SETVAL, 1);

  init_buffer(pc);

  pid_t pid;

  for (int i = 0 ; i < N_CONS ; i++){
    pid = fork ();
    if (pid == 0){
      consuma(ds_sem,pc);
      exit(0);
    }
  }
  for (int i = 0 ; i < N_PROD ; i++){
    pid = fork ();
    if (pid == 0){
      produci(ds_sem,pc);
      exit(0);
    }
  }

  for (int i = 0 ; i < (N_PROD + N_CONS) ; i++)
    wait (NULL);

  printf("Terminazione processo\n" );

  shmctl(ds_shmem, IPC_RMID, 0);
  semctl(ds_sem, 4, IPC_RMID);

  return 0;
}
