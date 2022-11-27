#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

#define SPAZIO_DISPONIBILE 0
#define MESSAGGIO_DISPONIBILE 1
#define MUTEX_STATE 2

int wait_sem(int ds_sem, int num_sem);
int signal_sem(int ds_sem, int num_sem);

#endif //_SEMAPHORE_H_
