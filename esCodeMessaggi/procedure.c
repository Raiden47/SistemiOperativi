#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "procedure.h"

void produttore (int queue, char * text){
  message m;

  m.type = MSG_TYPE;
  strcpy(m.text, text);

  msgsnd(queue,(void *)&m, sizeof(message)-sizeof(long),IPC_NOWAIT);
  printf("|___ Messaggio inviato ___|___ %s ___|\n", m.text);


}

void consumatore (int queue){
  message m;

  msgrcv(queue, (void *)&m, sizeof(message)-sizeof(long),MSG_TYPE,0);
  printf("|___ Messaggio ricevuto ___|___ %s ___|\n", m.text);
  print_msg_info(queue);

}

void print_msg_info (int queue){
  struct msgid_ds msg_id;
  msgctl(queue, IPC_STAT, &msg_id);
  char *time_sender(&msg_id.msg_stime);
  char *time_receiver(&msg_id.msg_rtime);
  char *time_ctime(&msg_id.msg_ctime);

  printf("<--- Time Sender --- %s --->\n<--- Time Receiver --- %s --->\n<--- Current Time --- %s --->\n", time_sender, time_receiver, time_ctime);
  printf("<--- Message Number --- %ld --->\n",msg_id.msg_qnum);
}
