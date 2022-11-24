#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/sem.h>

#include "procedure.h"
#include "semaphore.h"

int main () {

  key_t k_shmem = IPC_PRIVATE;
  key_t k_sem = IPC_PRIVATE;

  int ds_shmem = shmget(k_shmem, sizeof(int), IPC_CREAT | 0664);
  if (ds_shmem < 0)
    {perror("Errore SHMGET"); _exit(1);}
  int *val = (int*) shmat(ds_shmem, NULL, 0);

  *val = 0;

  int ds_sem = semget(k_sem, 2, IPC_CREAT | 0664);

  semctl (ds_sem, SPAZIO_DISPONIBILE, SETVAL, 1);
  semctl (ds_sem, MESSAGGIO_DISPONIBILE, SETVAL, 0);

  pid_t pid;

  for (int i = 0 ; i < 2 ; i++){

    pid = fork();
    if (pid < 0){
      perror("Errore FORK");
      _exit(1);
    }

    if (pid == 0){
      if (i == 0 ){
        printf("<--- [%d] Sono il produttore e ce l'ho duro --->\n", getpid());
        produttore(val, ds_sem);
      } else {
        printf("<--- [%d] Sono il consumatore e te lo butto a culo --->\n", getpid());
        consumatore(val, ds_sem);
      }
      exit (0);
    }
  }

  for (int i = 0 ; i < 2 ; i++)
    wait(NULL);

  printf("|--- Rimuovo la variabile condivisa e i semafori ---|\n");

  shmctl(ds_shmem,IPC_RMID, NULL);
  semctl(ds_sem, 0, IPC_RMID);

  return 0;
}
