#include "procedure.h"

int ricerca_min(int vector[], int init_pos){
  int min = vector[init_pos];

  for (int i = (init_pos + 1) ; i < N_ELEM ; i++)
    if (min > vector[i])
      min = vector[i];

  return min;
}
