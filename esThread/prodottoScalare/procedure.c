#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "procedure.h"

void init_buffer (struct t_par * par){
  for (int i = 0 ; i < DIM ; i++){
    // par->vett->v1[i] = 2;
    // par->vett->v2[i] = 2;

    par->v1[i] = 2;
    par->v2[i] = 2;
  }
}
