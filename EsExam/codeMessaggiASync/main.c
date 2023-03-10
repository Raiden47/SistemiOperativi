#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/wait.h>

#include "procedure.h"

int main (){

  key_t k_msg = IPC_PRIVATE;

  int queue = msgget(k_msg, IPC_CREAT | 0664);

  pid_t pid;

  for (int i = 0 ; i < N_PROC ; i++){
    pid = fork ();
    if (pid == 0 && i == 0){
      produci(queue);
      exit(0);
    } else if (pid == 0 && i == 1){
      consuma(queue);
      exit(0);
    }
  }

  for (int i = 0 ; i < N_PROC ; i++){
    wait(NULL);
  }

  msgctl (queue, IPC_RMID, 0);


  return 0;
}
