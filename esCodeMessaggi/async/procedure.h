#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>

#define MSG_TYPE 1
#define N_PROC 2
#define N_F_CALL 10   //Number function call


typedef char msg [40];

typedef struct {
  long type;
  msg text;
}message;

void produttore(int , char * );
void consumatore(int );
void print_msg_info(int );

#endif //_PROCEDURE_H_
