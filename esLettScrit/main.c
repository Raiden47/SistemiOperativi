#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <sys/wait.h>
#include <sys/shm.h>

#include "semaphore.h"
#include "procedure.h"

int main(){
  key_t k_shm = IPC_PRIVATE;
  key_t k_sem = IPC_PRIVATE;

  int ds_shm = shmget(k_shm, sizeof(buffer *), IPC_CREAT | 0664);
  int ds_sem = semget(k_sem, 2, IPC_CREAT | 0664);

  buffer * shm = (buffer *) shmat(ds_shm, NULL, 0);

  semctl(ds_sem,MUTEXL,SETVAL,1);
  semctl(ds_sem,SYNCH,SETVAL,1);

  shm->num_lettori = 0;
  shm->messaggio = 0;

  pid_t pid;
  for (int i = 0 ; i < N_SCRITTORI ; i++){

    pid = fork();
    if (pid == 0){
      srand(getpid()*time(NULL));
      printf("<--- Solo lo scrittore [%d] --->\n", getpid());
      scrittore(ds_sem,shm);
      exit(0);
    }
  }

  for (int i = 0 ; i < N_LETTORI ; i++){

    pid = fork();
    if (pid == 0){
      printf("<--- Solo il lettore [%d] --->\n", getpid());
      lettore(ds_sem,shm);
      exit(0);
    }
  }

  for (int i = 0 ; i < N_LETTORI + N_SCRITTORI ; i++)
    wait(NULL);

  printf("Processi terminati\n");

  shmctl(ds_shm, IPC_RMID, 0);
  semctl(ds_sem, 2, IPC_RMID);

  return 0;
}
