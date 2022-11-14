#include <stdio.h>
#include <stdlib.h>
//#include <sys/exec.h>
#include <sys/wait.h>

int main (int argc, char *argv[]){

  execlp("git", "git", "add", "--all");
  perror("errore 1");
  execlp("git", "git", "commit", "-m", argv[1]);
  perror("errore 2");
  execlp("git", "git", "push", "--set-upstream", "origin", "main");
  perror("errore 3");

  return 0;

}
