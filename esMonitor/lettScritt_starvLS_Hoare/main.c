#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>

#include "procedure.h"

int main (){

  pid_t pid;
  key_t k_shmem = IPC_PRIVATE;

  int shmem = shmget(k_shmem,sizeof(struct lettScritt *), IPC_CREAT | 0664);

  struct lettScritt * ls = (struct lettScritt *) shmat(shmem, NULL, 0);

  init_monitor(&ls->m,2);
  init_buffer(ls);

  for (int i = 0 ; i < NUM_SCRITT ; i++){
    pid = fork();
    if (pid == 0){
      printf("<- PID [%d] - Sono lo scrittore [%d] ->\n", getpid(), i);
      srand(getpid()*time(NULL));
      scrittura(ls, genera_numero());
      exit(0);
    }
  }

  for (int i = 0 ; i < NUM_LETT ; i++){
    pid = fork();
    if (pid == 0){
      printf("<- PID [%d] - Sono il lettore [%d] ->\n", getpid(), i);
      lettura(ls);
      exit(0);
    }
  }


  for (int i = 0 ; i < NUM_LETT + NUM_SCRITT ; i++)
    wait(NULL);

  remove_monitor(&ls->m);
  shmctl(shmem,IPC_RMID, 0);

  return 0;
}
