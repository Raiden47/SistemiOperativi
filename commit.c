#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *argv[]){

  printf("Messaggio da stampare inserire con il commit >> %s\n\n\n", argv[1]);
  execlp("ls", "ls", "-l", NULL);
  perror("errore 0");
  execlp("git", "git", "add", "--all", NULL);
  perror("errore 1");
  execlp("git", "git", "commit", "-m", argv[1], NULL);
  perror("errore 2");
  execlp("git", "git", "push", "--set-upstream", "origin", "main", NULL);
  perror("errore 3");

  return 0;

}
