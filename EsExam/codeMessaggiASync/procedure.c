#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "procedure.h"

void produci (int queue){

  msg m;
  t_msg text;
  for (int i = 0 ; i < DIM_MSG ; i++){
    printf("Messaggio generato\n" );
    sprintf(text, "Stringa [%d]\n", i);
    m.type = MSG_TYPE;
    //m->message = text;
    strcpy (m.message, text);
    msgsnd (queue, (void *)&m, sizeof(msg)-sizeof(long), 0);

  }

}

void consuma (int queue){
  msg m;
  for (int i = 0 ; i < DIM_MSG ; i++){
    msgrcv (queue, (void *)&m, sizeof(msg)-sizeof(long), MSG_TYPE, 0);
    printf("Messaggio letto - %s\n", m.message);
  }

}
