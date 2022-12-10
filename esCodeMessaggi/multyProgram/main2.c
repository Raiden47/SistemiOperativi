#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "procedure.h"

int main (){

  int id_queue = init_queue();

  srand(getpid()*time(NULL));
  printf("Sono il programma P2 con PID[%d]\n",getpid());

  produttore ((long)P2, id_queue);

  return 0;
}
