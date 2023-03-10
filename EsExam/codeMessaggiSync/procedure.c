#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "procedure.h"

void produci (int queue, t_msg txt){

  msg m;

  m.type = SYNCH_TYPE;
  msgsnd(queue, (void *)&m, sizeof(msg)-sizeof(long),0);
  printf("Synch request sent\n");

  msgrcv(queue, (void *)&m, sizeof(msg)-sizeof(long), ACK_REP, 0);
  printf("Ack received\n");

  m.type = MSG_TYPE;
  strcpy (m.message, txt);
  msgsnd(queue, (void *)&m, sizeof(msg)-sizeof(long),0);
  printf("Message sent\n");

}

void consuma (int queue){

  msg m;

  msgrcv(queue, (void *)&m, sizeof(msg)-sizeof(long), SYNCH_TYPE, 0);
  printf("Synch request received\n");

  m.type = ACK_REP;
  msgsnd(queue, (void *)&m, sizeof(msg)-sizeof(long), 0);
  printf("Ack sent\n");

  msgrcv(queue, (void *)&m, sizeof(msg)-sizeof(long), MSG_TYPE, 0);
  printf("Message received\n");

  printf("Message -> %s\n", m.message);

}
