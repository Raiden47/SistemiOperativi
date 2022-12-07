#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/wait.h>

#include "procedure.h"

int main (){

  int queue;

  pid_t pid;

  msg text;

  queue = msgget(IPC_PRIVATE, IPC_CREAT |0664);

  pid = fork();

  if (pid == 0){
    for (int j = 0 ; j < N_F_CALL ; j++){
      sprintf(text, "String [%d]",j);
      usleep(100);
      produttore(queue, text);
    }
    exit(0);
  } else {
    pid = fork();
    if (pid == 0){
      sleep(1);
      for (int j = 0 ; j < N_F_CALL ; j++){
        consumatore(queue);
      }
    }
    exit(0);
  }

  for (int i = 0 ; i < N_PROC ; i++)
    wait(NULL);

  msgctl(queue, IPC_RMID, 0);

  return 0;
}
