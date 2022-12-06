#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>

#define MSG_TYPE 1

typedef char msg [40];

struct {
  long type;
  msg text;
}message;

void produttore(int , char * );
void consumatore(int );
void print_msg_info(int );

#endif //_PROCEDURE_H_
