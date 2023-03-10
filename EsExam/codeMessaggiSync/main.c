#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/wait.h>

#include "procedure.h"

int main () {

  key_t k_queue = IPC_PRIVATE;
  int queue = msgget (k_queue, IPC_CREAT | 0664);

  t_msg txt;

  pid_t pid;

  for (int i = 0 ; i < N_MSG ; i++){
    pid = fork();
    sleep(1);
    if (pid == 0){
      consuma(queue);
      exit(0);
    }
  }

  for (int i = 0 ; i < N_MSG ; i++){
    pid = fork();
    sleep(2);
    if(pid == 0){
      printf("Prepare to send:\n\tMessage [%d]\n", i);
      sprintf(txt, "Message [%d]", i);
      produci (queue, txt);
      exit(0);
    }
  }

  for (int i = 0 ; i < (N_MSG * 2); i++)
    wait (NULL);

  msgctl(queue, IPC_RMID, 0);

  return 0;
}
