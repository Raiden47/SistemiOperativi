#ifndef _COMMON_
#define _COMMON_

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

#define QUEUE_REQ 1
#define PRINT_REQ 2
#define SERVER_REQ 3

#define BUFFER_DIM 10
typedef pid_t buf[BUFFER_DIM];

/* Definizione Tipi di Messaggi*/
//TODO
struct {
  long type;
  pid_t text ;
}msg;

struct {
  long type;
  pid_t buf(BUFFER_DIM);
}msg_buff;

/* Definizione Messaggio Richiesta del Client */
//TODO

/* Definizione Messaggio Richiesta del Server, contenente il buffer */
//TODO


/* Prototipi delle funzioni dei processi */
void printer(int msgq_print);
void server(int msgq_guest, int msgq_print);
void client(int msgq_guest);

#endif
