#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/wait.h>

#include "procedure.h"

int main (){

  int queue;
  pid_t pid;

  queue = msgget(IPC_PRIVATE,IPC_CREAT | 0664);

  initServiceQueue();

  pid = fork();
  if (pid == 0){
    printf("Sono il processo produttore\n");
    produttore(queue, "tropp fort");
    exit(0);
  } else {
    pid = fork();
    if (pid == 0){
      printf("Sono il processo consumatore\n");
      consumatore(queue);
      exit(0);
    }
  }

  for (int i = 0 ; i < 2 ; i++)
    wait(NULL);

  msgctl(queue, IPC_RMID, 0);
  removeServiceQueue();
  return 0;
}
