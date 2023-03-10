#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define MSG_TYPE 1
#define SYNCH_TYPE 2
#define ACK_REP 3

#define N_MSG 20

typedef char t_msg [50];

typedef struct msgbuf {
  long type;
  t_msg message;
} msg;

void produci (int queue, t_msg txt);
void consuma (int queue);

#endif //_PROCEDURE_H_
