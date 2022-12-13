#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/shm.h>

#include "procedure.h"

int main () {

  pid_t pid;
  key_t k_shmem = IPC_PRIVATE;
  int shmem = shmget(k_shmem, sizeof(struct prodCons *), IPC_CREAT | 0664);

  struct prodCons * pc = (struct prodCons *) shmat(shmem, NULL, 0);

  init_monitor(&pc->m ,2);
  init_buffer (pc);

  for (int i = 0 ; i < NUM_CONS ; i++){
    pid = fork();
    if (pid == 0){
      srand(getpid()*time(NULL));
      produttore(pc);
      exit(0);
    }
  }

  for (int i = 0 ; i < NUM_CONS ; i++){
    pid = fork();
    if (pid == 0){
      srand(getpid()*time(NULL));
      consumatore(pc);
      exit(0);
    }
  }

  for (int i = 0 ; i < NUM_PROD + NUM_CONS ; i++)
    wait(NULL);

  remove_monitor(&pc->m);
  shmctl(shmem, IPC_RMID, 0);

  return 0;
}
