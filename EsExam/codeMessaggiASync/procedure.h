#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define DIM_MSG 50
#define MSG_TYPE 1
#define N_PROC 2

typedef char t_msg [DIM_MSG];

typedef struct msgbuf{
  long type;
  t_msg message
} msg;

void produci (int queue);
void consuma (int queue);

#endif //_PROCEDURE_H_
