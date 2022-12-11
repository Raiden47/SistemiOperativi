#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>

#include "procedure.h"

int main(){

  pid_t pid;
  key_t k_shm = IPC_PRIVATE;

  int shm = shmget (k_shm, sizeof(struct prodCons *), IPC_CREAT | 0664);

  struct prodCons * pc = (struct prodCons *) shmat(shm, NULL, 0);

  init_monitor(&pc->m,2);


  for (int i = 0 ; i < NUM_PRODUTTORI ; i++){
    pid = fork();

    if (pid == 0){
      srand(getpid()*time(NULL));
      produzione(pc,rand()%90+10);
      exit(0);
    }
  }

  for (int i = 0 ; i < NUM_CONSUMATORI ; i++){
    pid = fork();

    if (pid == 0){
      consumazione(pc);
      exit(0);
    }
  }

  for (int i = 0 ; i < NUM_PRODUTTORI+NUM_CONSUMATORI ; i++)
    wait(NULL);

  remove_monitor(&pc->m);
  shmctl(shm, IPC_RMID, 0);

  return 0;
}
