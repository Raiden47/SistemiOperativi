#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "procedure.h"

static int queue1;
static int queue2;

void initServiceQueue(){
  queue1 = msgget(IPC_PRIVATE, IPC_CREAT | 0664);
  queue2 = msgget(IPC_PRIVATE, IPC_CREAT | 0664);
}


void removeServiceQueue(){
  msgctl(queue1, IPC_RMID, 0);
  msgctl(queue2, IPC_RMID, 0);
}


void sendSincronized(message * mess, int queue){
  message rqt;
  message asw;
  rqt.type = REQUEST_TO_SEND;
  strcpy(rqt.txt, "Request to send");
  msgsnd(queue1, &rqt, sizeof(message)-sizeof(long), 0);
  msgrcv(queue2,&asw, sizeof(message)-sizeof(long),OK_TO_SEND,0);
  msgsnd(queue, mess, sizeof(message)-sizeof(long),0);
}


void receiveBlock(message * mess, int queue, int typeMess){
  message rqt;
  message asw;
  msgrcv(queue1,&rqt,sizeof(message)-sizeof(long), REQUEST_TO_SEND,0);
  asw.type = OK_TO_SEND;
  strcpy(asw.txt, "Ready to send");
  msgsnd(queue2,&asw,sizeof(message)-sizeof(long),0);
  msgrcv(queue,mess,sizeof(message)-sizeof(long),typeMess,0);
}



void produttore(int queue, char * text){
  message mess;
  mess.type = MESSAGE;
  strcpy(mess.txt, text);
  sendSincronized(&mess,queue);
  printf("... Message sent : %s\n", mess.txt);
}


void consumatore(int queue){
  message mess;
  receiveBlock(&mess, queue, MESSAGE);
  printf("... Message received : %s\n", mess.txt);
}
