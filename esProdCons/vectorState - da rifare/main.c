#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <sys/wait.h>
#include <sys/shm.h>

#include "procedure.h"
#include "semaphore.h"

int main() {

  key_t k_shmem = IPC_PRIVATE;
  key_t k_sem = IPC_PRIVATE;

  int ds_shmem = shmget(k_shmem, sizeof(struct prodCons *), IPC_CREAT | 0664);
  if (ds_shmem < 0)
    {perror("Errore SHMGET"); exit(1);}

  struct prodCons *shmem = (struct prodCons *) shmat(ds_shmem, NULL, 0);
  if (shmem < 0)
    {perror("Errore SHMAT"); exit(1);}

  int ds_sem = semget(k_sem, 3, IPC_CREAT | 0664);
  if (ds_sem < 0)
    {perror("Errore SEMGET"); exit(1);}

  semctl(ds_sem, SPAZIO_DISPONIBILE, SETVAL, 1);
  semctl(ds_sem, MESSAGGIO_DISPONIBILE, SETVAL, 0);
  semctl(ds_sem, MUTEX_STATE, SETVAL, 1);

  pid_t pid;
  int p_add;

  for (int i = 0 ; i < N_CONSUMATORI ; i++){

    pid = fork();
    if (pid < 0)
      {perror("Errore FORK"); exit(1);}
    if (pid == 0) {
      consumatore(shmem, ds_sem);
      exit(getpid());
    }

  }

  for (int i = 0 ; i < N_PRODUTTORI ; i++){

    pid = fork();
    if (pid < 0)
      {perror("Errore FORK"); exit(1);}
    if (pid == 0) {
      produttore(shmem, ds_sem);
      exit(getpid());
    }

  }

  for (int i = 0 ; i < (N_CONSUMATORI + N_PRODUTTORI) ; i++){
    wait (&p_add);
    printf("|--- [%d] Processo terminato ---|\n", p_add);
  }

  shmctl(ds_shmem, IPC_RMID, 0);
  semctl(ds_sem, 3, IPC_RMID);


  return 0;
}
