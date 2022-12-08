#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>

#define REQUEST_TO_SEND 1
#define OK_TO_SEND 2
#define MESSAGE 3

typedef char msg [40];

typedef struct {
  long type;
  msg txt;
}message;

void initServiceQueue();
void removeServiceQueue();
void sendSincronized(message * , int );
void receiveBlock(message * , int , int );

void produttore(int , char * );
void consumatore(int );



#endif
