#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "procedure.h"

int init_queue (){
  key_t queue = ftok(FTOK_PATH,FTOK_CHAR);
  int id_queue = msgget(queue, IPC_CREAT | 0664);
  return id_queue;
}


void remove_queue (int id_queue){
  msgctl(id_queue, IPC_RMID, 0);
}


float genera_float (int l_sx, int l_dx){
  // float num = (float) (rand()%l_dx+l_sx);
  // return num;
  return (float)(rand()%l_dx+l_sx);
}


void calcolo_media (float x){
  // Forse non serve
}



void produttore (long p_id, int id_queue){
  msg_calc msg;
  msg.process = p_id;
  for (int i = 0 ; i < N_SND ; i++){
    msg.num = genera_float(10,90);
    msgsnd(id_queue,(void *)&msg,sizeof(msg_calc)-sizeof(long), 0);
    sleep(2);
  }
  printf("... Messaggi Inviati\n");
}


void consumatore (int id_queue){
  msg_calc msg;
  float m1 = 0;
  float m2 = 0;
  for (int i = 0 ; i < N_RCV ; i++){
    msgrcv (id_queue, (void *)&msg, sizeof(msg_calc)-sizeof(long),0,0);
    switch(msg.process){
      case P1:
        m1 += (msg.num/N_SND);
        break;
      case P2:
        m2 += (msg.num/N_SND);
        break;
    }
  }
  printf("La media dei numeri prodotti da P1 : %f\n", m1);
  printf("La media dei numeri prodotti da P2 : %f\n", m2);
}
