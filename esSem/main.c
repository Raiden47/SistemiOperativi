#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>
#include <errno.h>

#include "semaphore.h"

int main (){

  key_t k_shm = IPC_PRIVATE;
  key_t k_sem = IPC_PRIVATE;

  //******CREAZIONE VARIABILE CONDIVISA******
  int id_shm = shmget(k_shm, sizeof(int), IPC_CREAT | 0664);

  if (id_shm < 0){
    perror ("Errore SHMGET");
    _exit(1);
  }

  int * ptr = shmat(id_shm,0,0);

  if (ptr == (void*)-1){
    perror("Errore SHMAT");
    _exit(1);
  }

  *ptr = 0;
  printf("Variabile condivisa inizializzata con il valora : [%d]\n ", *ptr);

  //******CREAZIONE SEMAFORO******
  int id_sem = semget(k_sem, 1, IPC_CREAT | 0664);

  if (id_sem < 0){
    perror("Errore SEMGET");
    _exit(1);
  }

  semctl(id_sem, 0, SETVAL, 1);
  printf("Semaforo [%d] inizializzato ad 1\n", id_sem);

  for (int i = 0 ; i < N_PROC ; i++){

    pid_t pid = fork();

    if (pid < 0){
      perror("Errore FORK");
      _exit(1);
    }

    if (pid == 0){
      printf("Processo [%d] PID -[%d]- creato\n", i, getpid());

      for(int j = 0 ; j < N_OP ; j++){
        wait_sem(id_sem, 0);
        //******INIZIO SEZIONE CRITICA******
        int tmp = *ptr;
        printf("\t\t <Processo [%d] ha letto il valore [%d]>\n", i, tmp);
        *ptr = tmp + 1;
        printf("\t\t <Processo [%d] ha incrementato>\n", i);
        //******FINE SEZIONE CRITICA******
        signal_sem(id_sem,0);
      }
      _exit(0);
    }
  }

  for (int i = 0 ; i < N_PROC ; i++)
    wait(NULL);

  printf("Valore finale della variabile condivisa -> [%d]\n", *ptr);
  shmctl(id_shm, IPC_RMID, 0);
  semctl(id_sem, 0, IPC_RMID);

  return 0;
}
