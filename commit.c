#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *argv[]){

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
