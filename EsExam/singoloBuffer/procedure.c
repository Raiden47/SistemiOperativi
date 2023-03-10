#include <stdio.h>
#include <stdlib.h>

#include "semaphore.h"
#include "procedure.h"

void produci (int *sh_num, int ds_sem){

  wait_sem(ds_sem, PRODUCI);

  sleep(1);
  *sh_num = genera_num();

  sleep(1);
  printf("Valore prodotto [%d]\n", *sh_num);

  signal_sem (ds_sem, CONSUMA);

}


void consuma (int *sh_num, int ds_sem){

  wait_sem(ds_sem, CONSUMA);

  sleep(1);
  printf("Valore consumato [%d]\n", *sh_num);
  sleep(1);

  signal_sem(ds_sem, PRODUCI);
}



int genera_num(){
  return rand()%90+10;
}
