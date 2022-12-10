#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define FTOK_PATH "."
#define FTOK_CHAR 'a'

#define N_SND 11
#define N_RCV 22

#define P1 1
#define P2 2

typedef struct {
  long process;
  float num;
} msg_calc;

int init_queue ();
void remove_queue (int );
float genera_float (int , int );
void calcolo_media (float ); // Forse non serve

void produttore (long , int );
void consumatore (int );

#endif //_PROCEDURE_H_
