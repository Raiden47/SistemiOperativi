#include <time.h>
#include <stdlib.h>

#include "procedure.h"

int ricerca_min(int vector[], int init_pos){
  int min = vector[init_pos];

  for (int i = (init_pos + 1) ; i < (init_pos + N_ELEM) ; i++)
    if (min > vector[i])
      min = vector[i];

  return min;
}

void genera_array(int vector[]){
    srand(time(NULL));
    for (int i = 0 ; i < N_VAL ; i++)
      vector[i] = rand()%100+1;
}

int controllo (int vector[]){
  int min = vector[0];

  for (int i = 1 ; i < N_VAL ; i++)
    if (min > vector[i])
      min = vector[i];

  return min;
}
