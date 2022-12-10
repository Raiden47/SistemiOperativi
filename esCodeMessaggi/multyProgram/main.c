#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <sys/wait.h>

#include "procedure.h"

int main (){

  int id_queue;
  msg_calc msg;
  pid_t pid;


  id_queue = init_queue();

  pid = fork();
  if (pid == 0){
    execl("./P1", "P1",(char *)0);
    perror("Exec fallita\n");
    exit(1);
  }

  pid = fork();
  if (pid == 0){
    execl("./P2", "P2",(char *)0);
    perror("Exec fallita\n");
    exit(1);
  }

  pid = fork();
  if (pid == 0){
    execl("./P3", "P3",(char *)0);
    perror("Exec fallita\n");
    exit(1);
  }

  for (int i = 0 ; i < 3 ; i++)
    wait(NULL);

  remove_queue(id_queue);
  return 0;
}
