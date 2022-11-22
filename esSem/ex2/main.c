#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <sys/shm.h>
#include <sys/wait.h>

#include "semaphore.h"
#include "procedure.h"

int main(){

  key_t shm_key = IPC_PRIVATE;
  key_t sem_key = IPC_PRIVATE;

  //---Generazione dell'array
  int vett[N_VAL];
  genera_array(vett);

  //---Creazione della shared memory
  int shm = shmget(shm_key, sizeof(int), IPC_CREAT | 0664);

  if (shm < 0){
    perror("Errore SHMGET");
    _exit(1);
  }

  int *sh_bff = shmat(shm, NULL, 0);

  if (sh_bff == (void*)-1){
    perror("Errore SHMAT");
    _exit(1);
  }

  //---Inizializzo la shared memory al primo valore dell'array
  *sh_bff = vett[0];
  printf("|--- Valore inizializzato a [%d] ---|\n", *sh_bff);

  //---Creo un mutex
  int sem = semget(sem_key, 1, IPC_CREAT | 0664);

  if (sem < 0){
    perror("Errore SEMGET");
    _exit(1);
  }

  semctl(sem, 0, SETVAL, 1);

  pid_t pid;

  for (int i = 0 ; i < N_PROC ; i++){
    pid = fork();

    if (pid < 0){
      perror("Errore FORK");
      _exit(1);
    } else
      printf("[%d] Processo - PID [%d]\n", i, getpid());
    if (pid == 0){
      int min = ricerca_min(vett, (i*N_ELEM));

      //---Inizio sezione critica
      wait_sem(sem,0);
      printf("<--- PIN[%d] Controllo la memoria condivisa --->\n", getpid());
      if (*sh_bff > min){
        printf("<--- Aggiorno la memoria condivisa --->\n");
        *sh_bff = min;
        printf("|--- Valore aggiornato - [%d] ---|\n", *sh_bff);
      }
      signal_sem(sem,0);
      //---Fine sezione critica
      _exit(0);
    }
  }

  if (pid > 0){
    for (int i = 0 ; i < N_PROC ; i++)
      wait(NULL);
  }

  printf("<--- Il valore più piccolo e' [%d] --->\n", *sh_bff);

  //---Check
  if (*sh_bff == controllo(vett))
    printf("<--- Controllo effettuato - Il programma funziona correttamente --->\n");
  else
    printf("<--- Controllo effettuato - Il programma non funziona correttamente --->\n");

  shmctl(shm,IPC_RMID,0);
  semctl(sem,0,IPC_RMID);

  return 0;
}
