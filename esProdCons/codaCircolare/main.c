#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "procedure.h"
#include "semaphore.h"

int main () {

  key_t k_shmem = IPC_PRIVATE;
  key_t k_sem = IPC_PRIVATE;

  int ds_shmem = shmget (k_shmem, sizeof(struct prodcons), IPC_CREAT | 0664);

  if (ds_shmem < 0){
    perror("Errore SHMGET");
    exit(1);
  }

  struct prodcons *pc ;
  pc = (struct prodcons *) shmat(ds_shmem, NULL, 0);

  pc->testa = 0;
  pc->coda = 0;

  int ds_sem = semget (k_sem, 4, IPC_CREAT | 0664);
  if (ds_sem < 0){
      perror("Errore SEMGET");
      exit(1);
    }

    semctl(ds_sem, SPAZIO_DISPONIBILE, SETVAL, DIM_BUFFER);
    semctl(ds_sem, MESSAGGIO_DISPONIBILE, SETVAL, 0);
    semctl(ds_sem, MUTEX_P, SETVAL, 1);
    semctl(ds_sem, MUTEX_C, SETVAL, 1);

  pid_t pid;

  // Creo i produttori
  for (int i = 0 ; i < NUM_PRODUTTORI ; i++){
    pid = fork();

    if(pid < 0){
      perror("Errore FORK");
      exit(1);
    }

    if(pid == 0){
      printf("<--- [%d] Produttore --->\n", getpid());
      produttore(pc, ds_sem);
      exit(0);
    }
  }

  // Creo i consumatori
  for (int i = 0 ; i < NUM_CONSUMATORI ; i++){
    pid = fork();

    if(pid < 0){
      perror("Errore FORK");
      exit(1);
    }
    if(pid == 0){
      printf("<--- [%d] Consumatore --->\n", getpid());
      consumatore(pc, ds_sem);
      exit(0);
    }
  }

  for (int i = 0 ; i < NUM_CONSUMATORI + NUM_PRODUTTORI ; i++)
    wait(NULL);

  printf("<--- Rimuovo le risorse --->\n");

  shmctl(ds_shmem, IPC_RMID, 0);
  semctl(ds_sem, 4, IPC_RMID);

  return 0;

}
