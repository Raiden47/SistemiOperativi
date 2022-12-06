#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>

typedef long msg []

struct message{
  long type;
  char text[40];
}msg;

void produttore();
void consumatore();
void print_msg();

#endif //_PROCEDURE_H_
