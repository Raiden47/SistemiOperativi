#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <time.h>
#include <sys/wait.h>

#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define N_PROC 5

int main(){

  key_t key = IPC_PRIVATE;
  srand(time(NULL));

  int shm = shmget(key, sizeof(int), IPC_CREAT | 0664);

  if (shm < 0){
    perror("<-- Errore shmget -->");
    exit (1);
  }

  int *p = shmat(shm,NULL,0);
  if (p == (void*)-1){
    perror("<-- Errore shmat -->");
    exit(1);
  }

  *p = 111;

  key_t pid;

  for (int i = 0 ; i < N_PROC ; i++){

    printf("<-- Creazione figlio [%d] -->\n", i);
    pid = fork();

    if (pid < 0){
      perror("<-- Errore fork -->");
      exit (1);
    } else if (pid == 0){
      //Processo Figlio
      int temp = 100 + rand()%899;
      printf("<-- Sono il processo figlio con PID: §%d\n", getpid());
      printf("<-- Valore attuale della variabile condivisa: [%d]\n", *p);
      printf("<-- Cambio il valore della variabile condivisa con [%d]\n", temp);
      *p = temp;
      exit(0);
    }else if (pid > 0){
      wait (NULL);
      printf("<-- Tutti i figli hanno terminato -->\n");
      printf("<-- Valore della variabile condivisa: [%d]\n",*p);
    }

  }

  shmctl(shm, IPC_RMID, NULL);

  return 0;
}
